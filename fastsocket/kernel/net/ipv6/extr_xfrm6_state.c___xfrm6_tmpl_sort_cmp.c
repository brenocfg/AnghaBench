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
struct xfrm_tmpl {int mode; } ;

/* Variables and functions */
#define  XFRM_MODE_BEET 132 
#define  XFRM_MODE_IN_TRIGGER 131 
#define  XFRM_MODE_ROUTEOPTIMIZATION 130 
#define  XFRM_MODE_TRANSPORT 129 
#define  XFRM_MODE_TUNNEL 128 

__attribute__((used)) static int __xfrm6_tmpl_sort_cmp(void *p)
{
	struct xfrm_tmpl *v = p;
	switch (v->mode) {
	case XFRM_MODE_TRANSPORT:
		return 1;
#if defined(CONFIG_IPV6_MIP6) || defined(CONFIG_IPV6_MIP6_MODULE)
	case XFRM_MODE_ROUTEOPTIMIZATION:
	case XFRM_MODE_IN_TRIGGER:
		return 2;
#endif
	case XFRM_MODE_TUNNEL:
	case XFRM_MODE_BEET:
		return 3;
	}
	return 4;
}