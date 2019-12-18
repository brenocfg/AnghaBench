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
struct il3945_rxon_cmd {int dummy; } ;
struct il3945_powertable_cmd {int dummy; } ;

/* Variables and functions */
#define  C_POWER_TBL 129 
#define  C_RXON 128 

__attribute__((used)) static u16
il3945_get_hcmd_size(u8 cmd_id, u16 len)
{
	switch (cmd_id) {
	case C_RXON:
		return sizeof(struct il3945_rxon_cmd);
	case C_POWER_TBL:
		return sizeof(struct il3945_powertable_cmd);
	default:
		return len;
	}
}