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
typedef  int WORD ;
typedef  scalar_t__ DWORD_PTR ;
typedef  int /*<<< orphan*/  DWORD ;
typedef  int BYTE ;

/* Variables and functions */
 scalar_t__ MAC_REG_MAR0 ; 
 scalar_t__ MAC_REG_RCR ; 
 int /*<<< orphan*/  MACvSelectPage0 (scalar_t__) ; 
 int /*<<< orphan*/  MACvSelectPage1 (scalar_t__) ; 
 int PKT_TYPE_ALL_MULTICAST ; 
 int PKT_TYPE_BROADCAST ; 
 int PKT_TYPE_DIRECTED ; 
 int PKT_TYPE_ERROR_CRC ; 
 int PKT_TYPE_MULTICAST ; 
 int PKT_TYPE_PROMISCUOUS ; 
 int RCR_BROADCAST ; 
 int RCR_BSSID ; 
 int RCR_ERRCRC ; 
 int RCR_MULTICAST ; 
 int RCR_RXALLTYPE ; 
 int RCR_UNICAST ; 
 int /*<<< orphan*/  VNSvInPortB (scalar_t__,int*) ; 
 int /*<<< orphan*/  VNSvOutPortB (scalar_t__,int) ; 
 int /*<<< orphan*/  VNSvOutPortD (scalar_t__,int) ; 

void MACvSetPacketFilter (DWORD_PTR dwIoBase, WORD wFilterType)
{
    BYTE    byOldRCR;
    BYTE    byNewRCR = 0;

    // if only in DIRECTED mode, multicast-address will set to zero,
    // but if other mode exist (e.g. PROMISCUOUS), multicast-address
    // will be open
    if (wFilterType & PKT_TYPE_DIRECTED) {
        // set multicast address to accept none
        MACvSelectPage1(dwIoBase);
        VNSvOutPortD(dwIoBase + MAC_REG_MAR0, 0L);
        VNSvOutPortD(dwIoBase + MAC_REG_MAR0 + sizeof(DWORD), 0L);
        MACvSelectPage0(dwIoBase);
    }

    if (wFilterType & (PKT_TYPE_PROMISCUOUS | PKT_TYPE_ALL_MULTICAST)) {
        // set multicast address to accept all
        MACvSelectPage1(dwIoBase);
        VNSvOutPortD(dwIoBase + MAC_REG_MAR0, 0xFFFFFFFFL);
        VNSvOutPortD(dwIoBase + MAC_REG_MAR0 + sizeof(DWORD), 0xFFFFFFFFL);
        MACvSelectPage0(dwIoBase);
    }

    if (wFilterType & PKT_TYPE_PROMISCUOUS) {

        byNewRCR |= (RCR_RXALLTYPE | RCR_UNICAST | RCR_MULTICAST | RCR_BROADCAST);

        byNewRCR &= ~RCR_BSSID;
    }

    if (wFilterType & (PKT_TYPE_ALL_MULTICAST | PKT_TYPE_MULTICAST))
        byNewRCR |= RCR_MULTICAST;

    if (wFilterType & PKT_TYPE_BROADCAST)
        byNewRCR |= RCR_BROADCAST;

    if (wFilterType & PKT_TYPE_ERROR_CRC)
        byNewRCR |= RCR_ERRCRC;

    VNSvInPortB(dwIoBase + MAC_REG_RCR,  &byOldRCR);
    if (byNewRCR != byOldRCR) {
        // Modify the Receive Command Register
        VNSvOutPortB(dwIoBase + MAC_REG_RCR, byNewRCR);
    }
}