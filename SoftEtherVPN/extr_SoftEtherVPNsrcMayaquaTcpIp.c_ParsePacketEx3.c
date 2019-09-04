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
typedef  int /*<<< orphan*/  UINT ;
typedef  int /*<<< orphan*/  UCHAR ;
typedef  int /*<<< orphan*/  PKT ;

/* Variables and functions */
 int /*<<< orphan*/ * ParsePacketEx4 (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int,int,int) ; 

PKT *ParsePacketEx3(UCHAR *buf, UINT size, bool no_l3, UINT vlan_type_id, bool bridge_id_as_mac_address)
{
	return ParsePacketEx4(buf, size, no_l3, vlan_type_id, bridge_id_as_mac_address, false, false);
}