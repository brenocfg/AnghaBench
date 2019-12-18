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
typedef  int /*<<< orphan*/  u8 ;
typedef  int u16 ;
struct ks_net {scalar_t__ enabled; int /*<<< orphan*/  mac_addr; } ;

/* Variables and functions */
 int /*<<< orphan*/  KS_MARH ; 
 int /*<<< orphan*/  KS_MARL ; 
 int /*<<< orphan*/  KS_MARM ; 
 int /*<<< orphan*/  ks_start_rx (struct ks_net*) ; 
 int /*<<< orphan*/  ks_stop_rx (struct ks_net*) ; 
 int /*<<< orphan*/  ks_wrreg16 (struct ks_net*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static void ks_set_mac(struct ks_net *ks, u8 *data)
{
	u16 *pw = (u16 *)data;
	u16 w, u;

	ks_stop_rx(ks);  /* Stop receiving for reconfiguration */

	u = *pw++;
	w = ((u & 0xFF) << 8) | ((u >> 8) & 0xFF);
	ks_wrreg16(ks, KS_MARH, w);

	u = *pw++;
	w = ((u & 0xFF) << 8) | ((u >> 8) & 0xFF);
	ks_wrreg16(ks, KS_MARM, w);

	u = *pw;
	w = ((u & 0xFF) << 8) | ((u >> 8) & 0xFF);
	ks_wrreg16(ks, KS_MARL, w);

	memcpy(ks->mac_addr, data, 6);

	if (ks->enabled)
		ks_start_rx(ks);
}