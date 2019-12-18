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
struct efx_filter_spec {int type; int flags; } ;
typedef  enum efx_filter_table_id { ____Placeholder_efx_filter_table_id } efx_filter_table_id ;

/* Variables and functions */
 int /*<<< orphan*/  BUILD_BUG_ON (int) ; 
 int /*<<< orphan*/  EFX_BUG_ON_PARANOID (int) ; 
 int EFX_FILTER_FLAG_TX ; 
 int EFX_FILTER_MAC_FULL ; 
 int EFX_FILTER_MAC_WILD ; 
 int EFX_FILTER_TABLE_RX_IP ; 
 int EFX_FILTER_TABLE_RX_MAC ; 
 int EFX_FILTER_TABLE_TX_MAC ; 
 int EFX_FILTER_TCP_FULL ; 
 int EFX_FILTER_TCP_WILD ; 
 int EFX_FILTER_UDP_FULL ; 
 int EFX_FILTER_UDP_WILD ; 
 int EFX_FILTER_UNSPEC ; 

__attribute__((used)) static enum efx_filter_table_id
efx_filter_spec_table_id(const struct efx_filter_spec *spec)
{
	BUILD_BUG_ON(EFX_FILTER_TABLE_RX_IP != (EFX_FILTER_TCP_FULL >> 2));
	BUILD_BUG_ON(EFX_FILTER_TABLE_RX_IP != (EFX_FILTER_TCP_WILD >> 2));
	BUILD_BUG_ON(EFX_FILTER_TABLE_RX_IP != (EFX_FILTER_UDP_FULL >> 2));
	BUILD_BUG_ON(EFX_FILTER_TABLE_RX_IP != (EFX_FILTER_UDP_WILD >> 2));
	BUILD_BUG_ON(EFX_FILTER_TABLE_RX_MAC != (EFX_FILTER_MAC_FULL >> 2));
	BUILD_BUG_ON(EFX_FILTER_TABLE_RX_MAC != (EFX_FILTER_MAC_WILD >> 2));
	BUILD_BUG_ON(EFX_FILTER_TABLE_TX_MAC != EFX_FILTER_TABLE_RX_MAC + 2);
	EFX_BUG_ON_PARANOID(spec->type == EFX_FILTER_UNSPEC);
	return (spec->type >> 2) + ((spec->flags & EFX_FILTER_FLAG_TX) ? 2 : 0);
}