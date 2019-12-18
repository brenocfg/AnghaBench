#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int proto; } ;
struct xfrm_usersa_info {int family; int mode; TYPE_1__ id; } ;
struct nlattr {int dummy; } ;

/* Variables and functions */
#define  AF_INET 138 
#define  AF_INET6 137 
 int EAFNOSUPPORT ; 
 int EINVAL ; 
#define  IPPROTO_AH 136 
#define  IPPROTO_COMP 135 
#define  IPPROTO_DSTOPTS 134 
#define  IPPROTO_ESP 133 
#define  IPPROTO_ROUTING 132 
 size_t XFRMA_ALG_AEAD ; 
 size_t XFRMA_ALG_AUTH ; 
 size_t XFRMA_ALG_AUTH_TRUNC ; 
 size_t XFRMA_ALG_COMP ; 
 size_t XFRMA_ALG_CRYPT ; 
 size_t XFRMA_COADDR ; 
 size_t XFRMA_ENCAP ; 
 size_t XFRMA_SEC_CTX ; 
#define  XFRM_MODE_BEET 131 
#define  XFRM_MODE_ROUTEOPTIMIZATION 130 
#define  XFRM_MODE_TRANSPORT 129 
#define  XFRM_MODE_TUNNEL 128 
 int verify_aead (struct nlattr**) ; 
 int verify_auth_trunc (struct nlattr**) ; 
 int verify_one_alg (struct nlattr**,size_t) ; 
 int verify_sec_ctx_len (struct nlattr**) ; 

__attribute__((used)) static int verify_newsa_info(struct xfrm_usersa_info *p,
			     struct nlattr **attrs)
{
	int err;

	err = -EINVAL;
	switch (p->family) {
	case AF_INET:
		break;

	case AF_INET6:
#if defined(CONFIG_IPV6) || defined(CONFIG_IPV6_MODULE)
		break;
#else
		err = -EAFNOSUPPORT;
		goto out;
#endif

	default:
		goto out;
	}

	err = -EINVAL;
	switch (p->id.proto) {
	case IPPROTO_AH:
		if ((!attrs[XFRMA_ALG_AUTH]	&&
		     !attrs[XFRMA_ALG_AUTH_TRUNC]) ||
		    attrs[XFRMA_ALG_AEAD]	||
		    attrs[XFRMA_ALG_CRYPT]	||
		    attrs[XFRMA_ALG_COMP])
			goto out;
		break;

	case IPPROTO_ESP:
		if (attrs[XFRMA_ALG_COMP])
			goto out;
		if (!attrs[XFRMA_ALG_AUTH] &&
		    !attrs[XFRMA_ALG_AUTH_TRUNC] &&
		    !attrs[XFRMA_ALG_CRYPT] &&
		    !attrs[XFRMA_ALG_AEAD])
			goto out;
		if ((attrs[XFRMA_ALG_AUTH] ||
		     attrs[XFRMA_ALG_AUTH_TRUNC] ||
		     attrs[XFRMA_ALG_CRYPT]) &&
		    attrs[XFRMA_ALG_AEAD])
			goto out;
		break;

	case IPPROTO_COMP:
		if (!attrs[XFRMA_ALG_COMP]	||
		    attrs[XFRMA_ALG_AEAD]	||
		    attrs[XFRMA_ALG_AUTH]	||
		    attrs[XFRMA_ALG_AUTH_TRUNC]	||
		    attrs[XFRMA_ALG_CRYPT])
			goto out;
		break;

#if defined(CONFIG_IPV6) || defined(CONFIG_IPV6_MODULE)
	case IPPROTO_DSTOPTS:
	case IPPROTO_ROUTING:
		if (attrs[XFRMA_ALG_COMP]	||
		    attrs[XFRMA_ALG_AUTH]	||
		    attrs[XFRMA_ALG_AUTH_TRUNC]	||
		    attrs[XFRMA_ALG_AEAD]	||
		    attrs[XFRMA_ALG_CRYPT]	||
		    attrs[XFRMA_ENCAP]		||
		    attrs[XFRMA_SEC_CTX]	||
		    !attrs[XFRMA_COADDR])
			goto out;
		break;
#endif

	default:
		goto out;
	}

	if ((err = verify_aead(attrs)))
		goto out;
	if ((err = verify_auth_trunc(attrs)))
		goto out;
	if ((err = verify_one_alg(attrs, XFRMA_ALG_AUTH)))
		goto out;
	if ((err = verify_one_alg(attrs, XFRMA_ALG_CRYPT)))
		goto out;
	if ((err = verify_one_alg(attrs, XFRMA_ALG_COMP)))
		goto out;
	if ((err = verify_sec_ctx_len(attrs)))
		goto out;

	err = -EINVAL;
	switch (p->mode) {
	case XFRM_MODE_TRANSPORT:
	case XFRM_MODE_TUNNEL:
	case XFRM_MODE_ROUTEOPTIMIZATION:
	case XFRM_MODE_BEET:
		break;

	default:
		goto out;
	}

	err = 0;

out:
	return err;
}