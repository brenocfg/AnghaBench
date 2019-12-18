#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct xfrm_algo {char* alg_name; } ;
struct nlattr {int dummy; } ;
typedef  enum xfrm_attr_type_t { ____Placeholder_xfrm_attr_type_t } xfrm_attr_type_t ;

/* Variables and functions */
 int CRYPTO_MAX_ALG_NAME ; 
 int EINVAL ; 
#define  XFRMA_ALG_AUTH 130 
#define  XFRMA_ALG_COMP 129 
#define  XFRMA_ALG_CRYPT 128 
 struct xfrm_algo* nla_data (struct nlattr*) ; 
 scalar_t__ nla_len (struct nlattr*) ; 
 scalar_t__ xfrm_alg_len (struct xfrm_algo*) ; 

__attribute__((used)) static int verify_one_alg(struct nlattr **attrs, enum xfrm_attr_type_t type)
{
	struct nlattr *rt = attrs[type];
	struct xfrm_algo *algp;

	if (!rt)
		return 0;

	algp = nla_data(rt);
	if (nla_len(rt) < xfrm_alg_len(algp))
		return -EINVAL;

	switch (type) {
	case XFRMA_ALG_AUTH:
	case XFRMA_ALG_CRYPT:
	case XFRMA_ALG_COMP:
		break;

	default:
		return -EINVAL;
	}

	algp->alg_name[CRYPTO_MAX_ALG_NAME - 1] = '\0';
	return 0;
}