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
typedef  int /*<<< orphan*/  u64 ;

/* Variables and functions */
 int /*<<< orphan*/  snprintf (char*,int,char*,int,int,int,int,int,int,int,int) ; 
 int /*<<< orphan*/  u64_to_wwn (int /*<<< orphan*/ ,int*) ; 

void fcoe_wwn_to_str(u64 wwn, char *buf, int len)
{
	u8 wwpn[8];

	u64_to_wwn(wwn, wwpn);
	snprintf(buf, len, "%02x%02x%02x%02x%02x%02x%02x%02x",
		 wwpn[0], wwpn[1], wwpn[2], wwpn[3],
		 wwpn[4], wwpn[5], wwpn[6], wwpn[7]);
}