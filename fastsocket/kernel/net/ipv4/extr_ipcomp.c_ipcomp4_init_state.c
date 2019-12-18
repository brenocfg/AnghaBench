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
struct TYPE_2__ {int mode; scalar_t__ header_len; } ;
struct xfrm_state {TYPE_1__ props; } ;
struct iphdr {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
#define  XFRM_MODE_TRANSPORT 129 
#define  XFRM_MODE_TUNNEL 128 
 int /*<<< orphan*/  ipcomp_destroy (struct xfrm_state*) ; 
 int ipcomp_init_state (struct xfrm_state*) ; 
 int ipcomp_tunnel_attach (struct xfrm_state*) ; 

__attribute__((used)) static int ipcomp4_init_state(struct xfrm_state *x)
{
	int err = -EINVAL;

	x->props.header_len = 0;
	switch (x->props.mode) {
	case XFRM_MODE_TRANSPORT:
		break;
	case XFRM_MODE_TUNNEL:
		x->props.header_len += sizeof(struct iphdr);
		break;
	default:
		goto out;
	}

	err = ipcomp_init_state(x);
	if (err)
		goto out;

	if (x->props.mode == XFRM_MODE_TUNNEL) {
		err = ipcomp_tunnel_attach(x);
		if (err)
			goto error_tunnel;
	}

	err = 0;
out:
	return err;

error_tunnel:
	ipcomp_destroy(x);
	goto out;
}