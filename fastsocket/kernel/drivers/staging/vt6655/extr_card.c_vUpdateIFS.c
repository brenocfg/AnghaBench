#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {scalar_t__ byPacketType; int uSlot; int uSIFS; int uDIFS; int wBasicRate; scalar_t__ byRFType; scalar_t__ PortOffset; scalar_t__ uEIFS; int /*<<< orphan*/  uCwMax; void* uCwMin; scalar_t__ bShortSlotTime; } ;
typedef  int /*<<< orphan*/  PVOID ;
typedef  TYPE_1__* PSDevice ;
typedef  int BYTE ;

/* Variables and functions */
 int /*<<< orphan*/  C_CWMAX ; 
 void* C_CWMIN_A ; 
 void* C_CWMIN_B ; 
 scalar_t__ C_EIFS ; 
 void* C_SIFS_A ; 
 void* C_SIFS_BG ; 
 int C_SLOT_LONG ; 
 int C_SLOT_SHORT ; 
 scalar_t__ MAC_REG_CWMAXMIN0 ; 
 scalar_t__ MAC_REG_DIFS ; 
 scalar_t__ MAC_REG_EIFS ; 
 scalar_t__ MAC_REG_SIFS ; 
 scalar_t__ MAC_REG_SLOT ; 
 scalar_t__ PK_TYPE_11A ; 
 scalar_t__ PK_TYPE_11B ; 
 scalar_t__ RF_RFMD2959 ; 
 int /*<<< orphan*/  VNSvOutPortB (scalar_t__,int) ; 

void vUpdateIFS (PVOID pDeviceHandler)
{
    //Set SIFS, DIFS, EIFS, SlotTime, CwMin
    PSDevice pDevice = (PSDevice) pDeviceHandler;

    BYTE byMaxMin = 0;
    if (pDevice->byPacketType==PK_TYPE_11A) {//0000 0000 0000 0000,11a
        pDevice->uSlot = C_SLOT_SHORT;
        pDevice->uSIFS = C_SIFS_A;
        pDevice->uDIFS = C_SIFS_A + 2*C_SLOT_SHORT;
        pDevice->uCwMin = C_CWMIN_A;
        byMaxMin = 4;
    }
    else if (pDevice->byPacketType==PK_TYPE_11B) {//0000 0001 0000 0000,11b
        pDevice->uSlot = C_SLOT_LONG;
        pDevice->uSIFS = C_SIFS_BG;
        pDevice->uDIFS = C_SIFS_BG + 2*C_SLOT_LONG;
	    pDevice->uCwMin = C_CWMIN_B;
        byMaxMin = 5;
    }
    else { // PK_TYPE_11GA & PK_TYPE_11GB
        pDevice->uSIFS = C_SIFS_BG;
        if (pDevice->bShortSlotTime) {
            pDevice->uSlot = C_SLOT_SHORT;
        } else {
	        pDevice->uSlot = C_SLOT_LONG;
	    }
	    pDevice->uDIFS = C_SIFS_BG + 2*pDevice->uSlot;
        if (pDevice->wBasicRate & 0x0150) { //0000 0001 0101 0000,24M,12M,6M
            pDevice->uCwMin = C_CWMIN_A;
            byMaxMin = 4;
        }
        else {
            pDevice->uCwMin = C_CWMIN_B;
            byMaxMin = 5;
        }
    }

    pDevice->uCwMax = C_CWMAX;
    pDevice->uEIFS = C_EIFS;
    if (pDevice->byRFType == RF_RFMD2959) {
        // bcs TX_PE will reserve 3 us
        VNSvOutPortB(pDevice->PortOffset + MAC_REG_SIFS, (BYTE)(pDevice->uSIFS - 3));
        VNSvOutPortB(pDevice->PortOffset + MAC_REG_DIFS, (BYTE)(pDevice->uDIFS - 3));
    } else {
        VNSvOutPortB(pDevice->PortOffset + MAC_REG_SIFS, (BYTE)pDevice->uSIFS);
        VNSvOutPortB(pDevice->PortOffset + MAC_REG_DIFS, (BYTE)pDevice->uDIFS);
    }
    VNSvOutPortB(pDevice->PortOffset + MAC_REG_EIFS, (BYTE)pDevice->uEIFS);
    VNSvOutPortB(pDevice->PortOffset + MAC_REG_SLOT, (BYTE)pDevice->uSlot);
    byMaxMin |= 0xA0;//1010 1111,C_CWMAX = 1023
    VNSvOutPortB(pDevice->PortOffset + MAC_REG_CWMAXMIN0, (BYTE)byMaxMin);
}