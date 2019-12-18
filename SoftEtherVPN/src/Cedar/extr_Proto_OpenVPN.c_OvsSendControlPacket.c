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
typedef  int /*<<< orphan*/  OPENVPN_CHANNEL ;

/* Variables and functions */
 int /*<<< orphan*/  OvsSendControlPacketEx (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 

void OvsSendControlPacket(OPENVPN_CHANNEL *c, UCHAR opcode, UCHAR *data, UINT data_size)
{
	OvsSendControlPacketEx(c, opcode, data, data_size, false);
}