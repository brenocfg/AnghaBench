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
typedef  scalar_t__ u16 ;
struct efx_filter_spec {int flags; scalar_t__ type; int* data; } ;

/* Variables and functions */
 int /*<<< orphan*/  EFX_BUG_ON_PARANOID (int) ; 
 int EFX_FILTER_FLAG_RX ; 
 int EFX_FILTER_FLAG_TX ; 
 scalar_t__ EFX_FILTER_MAC_FULL ; 
 scalar_t__ EFX_FILTER_MAC_WILD ; 
 scalar_t__ EFX_FILTER_UNSPEC ; 
 scalar_t__ EFX_FILTER_VID_UNSPEC ; 
 int EPROTONOSUPPORT ; 

int efx_filter_set_eth_local(struct efx_filter_spec *spec,
			     u16 vid, const u8 *addr)
{
	EFX_BUG_ON_PARANOID(!(spec->flags &
			      (EFX_FILTER_FLAG_RX | EFX_FILTER_FLAG_TX)));

	/* This cannot currently be combined with other filtering */
	if (spec->type != EFX_FILTER_UNSPEC)
		return -EPROTONOSUPPORT;

	if (vid == EFX_FILTER_VID_UNSPEC) {
		spec->type = EFX_FILTER_MAC_WILD;
		spec->data[0] = 0;
	} else {
		spec->type = EFX_FILTER_MAC_FULL;
		spec->data[0] = vid;
	}

	spec->data[1] = addr[2] << 24 | addr[3] << 16 | addr[4] << 8 | addr[5];
	spec->data[2] = addr[0] << 8 | addr[1];
	return 0;
}