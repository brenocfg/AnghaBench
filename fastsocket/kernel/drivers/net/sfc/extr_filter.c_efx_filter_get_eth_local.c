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
typedef  int u8 ;
typedef  int u16 ;
struct efx_filter_spec {int type; int* data; } ;

/* Variables and functions */
#define  EFX_FILTER_MAC_FULL 129 
#define  EFX_FILTER_MAC_WILD 128 
 int EFX_FILTER_VID_UNSPEC ; 
 int EINVAL ; 

int efx_filter_get_eth_local(const struct efx_filter_spec *spec,
			     u16 *vid, u8 *addr)
{
	switch (spec->type) {
	case EFX_FILTER_MAC_WILD:
		*vid = EFX_FILTER_VID_UNSPEC;
		break;
	case EFX_FILTER_MAC_FULL:
		*vid = spec->data[0];
		break;
	default:
		return -EINVAL;
	}

	addr[0] = spec->data[2] >> 8;
	addr[1] = spec->data[2];
	addr[2] = spec->data[1] >> 24;
	addr[3] = spec->data[1] >> 16;
	addr[4] = spec->data[1] >> 8;
	addr[5] = spec->data[1];
	return 0;
}