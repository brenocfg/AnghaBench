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
typedef  scalar_t__ DWORD_PTR ;
typedef  int BYTE ;
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  IFRFbWriteEmbeded (scalar_t__,int /*<<< orphan*/ ) ; 
 scalar_t__ MAC_REG_CHANNEL ; 
 int /*<<< orphan*/  MACvTimer0MicroSDelay (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SWITCH_CHANNEL_DELAY_AL2230 ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  VNSvOutPortB (scalar_t__,int) ; 
 int /*<<< orphan*/ * dwAL2230ChannelTable0 ; 
 int /*<<< orphan*/ * dwAL2230ChannelTable1 ; 

BOOL RFbAL2230SelectChannel (DWORD_PTR dwIoBase, BYTE byChannel)
{
    BOOL    bResult;

    bResult = TRUE;

    bResult &= IFRFbWriteEmbeded (dwIoBase, dwAL2230ChannelTable0[byChannel-1]);
    bResult &= IFRFbWriteEmbeded (dwIoBase, dwAL2230ChannelTable1[byChannel-1]);

    // Set Channel[7] = 0 to tell H/W channel is changing now.
    VNSvOutPortB(dwIoBase + MAC_REG_CHANNEL, (byChannel & 0x7F));
    MACvTimer0MicroSDelay(dwIoBase, SWITCH_CHANNEL_DELAY_AL2230);
    // Set Channel[7] = 1 to tell H/W channel change is done.
    VNSvOutPortB(dwIoBase + MAC_REG_CHANNEL, (byChannel | 0x80));

    return bResult;
}