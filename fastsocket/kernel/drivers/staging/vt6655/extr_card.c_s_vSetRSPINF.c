#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  WORD ;
typedef  int /*<<< orphan*/  VOID ;
struct TYPE_4__ {scalar_t__ PortOffset; } ;
typedef  int /*<<< orphan*/  PVOID ;
typedef  TYPE_1__* PSDevice ;
typedef  int /*<<< orphan*/  CARD_PHY_TYPE ;
typedef  int /*<<< orphan*/  BYTE ;

/* Variables and functions */
 int /*<<< orphan*/  BBvCaculateParameter (TYPE_1__*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ MAC_REG_RSPINF_A_12 ; 
 scalar_t__ MAC_REG_RSPINF_A_18 ; 
 scalar_t__ MAC_REG_RSPINF_A_24 ; 
 scalar_t__ MAC_REG_RSPINF_A_36 ; 
 scalar_t__ MAC_REG_RSPINF_A_48 ; 
 scalar_t__ MAC_REG_RSPINF_A_54 ; 
 scalar_t__ MAC_REG_RSPINF_A_6 ; 
 scalar_t__ MAC_REG_RSPINF_A_72 ; 
 scalar_t__ MAC_REG_RSPINF_A_9 ; 
 scalar_t__ MAC_REG_RSPINF_B_1 ; 
 scalar_t__ MAC_REG_RSPINF_B_11 ; 
 scalar_t__ MAC_REG_RSPINF_B_2 ; 
 scalar_t__ MAC_REG_RSPINF_B_5 ; 
 int /*<<< orphan*/  MACvSelectPage0 (scalar_t__) ; 
 int /*<<< orphan*/  MACvSelectPage1 (scalar_t__) ; 
 int /*<<< orphan*/  MAKEDWORD (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MAKEWORD (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PK_TYPE_11B ; 
 int /*<<< orphan*/  RATE_11M ; 
 int /*<<< orphan*/  RATE_12M ; 
 int /*<<< orphan*/  RATE_18M ; 
 int /*<<< orphan*/  RATE_1M ; 
 int /*<<< orphan*/  RATE_24M ; 
 int /*<<< orphan*/  RATE_2M ; 
 int /*<<< orphan*/  RATE_36M ; 
 int /*<<< orphan*/  RATE_48M ; 
 int /*<<< orphan*/  RATE_54M ; 
 int /*<<< orphan*/  RATE_5M ; 
 int /*<<< orphan*/  RATE_6M ; 
 int /*<<< orphan*/  RATE_9M ; 
 int /*<<< orphan*/  VNSvOutPortD (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  VNSvOutPortW (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  VNTWIFIbyGetACKTxRate (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  s_vCaculateOFDMRParameter (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static
VOID
s_vSetRSPINF (PSDevice pDevice, CARD_PHY_TYPE ePHYType, PVOID pvSupportRateIEs, PVOID pvExtSupportRateIEs)
{
    BYTE  byServ = 0, bySignal = 0; // For CCK
    WORD  wLen = 0;
    BYTE  byTxRate = 0, byRsvTime = 0;    // For OFDM

    //Set to Page1
    MACvSelectPage1(pDevice->PortOffset);

    //RSPINF_b_1
    BBvCaculateParameter(pDevice,
                         14,
                         VNTWIFIbyGetACKTxRate(RATE_1M, pvSupportRateIEs, pvExtSupportRateIEs),
                         PK_TYPE_11B,
                         &wLen,
                         &byServ,
                         &bySignal
    );

    VNSvOutPortD(pDevice->PortOffset + MAC_REG_RSPINF_B_1, MAKEDWORD(wLen,MAKEWORD(bySignal,byServ)));
    ///RSPINF_b_2
    BBvCaculateParameter(pDevice,
                         14,
                         VNTWIFIbyGetACKTxRate(RATE_2M, pvSupportRateIEs, pvExtSupportRateIEs),
                         PK_TYPE_11B,
                         &wLen,
                         &byServ,
                         &bySignal
    );

    VNSvOutPortD(pDevice->PortOffset + MAC_REG_RSPINF_B_2, MAKEDWORD(wLen,MAKEWORD(bySignal,byServ)));
    //RSPINF_b_5
    BBvCaculateParameter(pDevice,
                         14,
                         VNTWIFIbyGetACKTxRate(RATE_5M, pvSupportRateIEs, pvExtSupportRateIEs),
                         PK_TYPE_11B,
                         &wLen,
                         &byServ,
                         &bySignal
    );

    VNSvOutPortD(pDevice->PortOffset + MAC_REG_RSPINF_B_5, MAKEDWORD(wLen,MAKEWORD(bySignal,byServ)));
    //RSPINF_b_11
    BBvCaculateParameter(pDevice,
                         14,
                         VNTWIFIbyGetACKTxRate(RATE_11M, pvSupportRateIEs, pvExtSupportRateIEs),
                         PK_TYPE_11B,
                         &wLen,
                         &byServ,
                         &bySignal
    );

    VNSvOutPortD(pDevice->PortOffset + MAC_REG_RSPINF_B_11, MAKEDWORD(wLen,MAKEWORD(bySignal,byServ)));
    //RSPINF_a_6
    s_vCaculateOFDMRParameter(RATE_6M,
                              ePHYType,
                              &byTxRate,
                              &byRsvTime);
    VNSvOutPortW(pDevice->PortOffset + MAC_REG_RSPINF_A_6, MAKEWORD(byTxRate,byRsvTime));
    //RSPINF_a_9
    s_vCaculateOFDMRParameter(RATE_9M,
                              ePHYType,
                              &byTxRate,
                              &byRsvTime);
    VNSvOutPortW(pDevice->PortOffset + MAC_REG_RSPINF_A_9, MAKEWORD(byTxRate,byRsvTime));
    //RSPINF_a_12
    s_vCaculateOFDMRParameter(RATE_12M,
                              ePHYType,
                              &byTxRate,
                              &byRsvTime);
    VNSvOutPortW(pDevice->PortOffset + MAC_REG_RSPINF_A_12, MAKEWORD(byTxRate,byRsvTime));
    //RSPINF_a_18
    s_vCaculateOFDMRParameter(RATE_18M,
                              ePHYType,
                              &byTxRate,
                              &byRsvTime);
    VNSvOutPortW(pDevice->PortOffset + MAC_REG_RSPINF_A_18, MAKEWORD(byTxRate,byRsvTime));
    //RSPINF_a_24
    s_vCaculateOFDMRParameter(RATE_24M,
                              ePHYType,
                              &byTxRate,
                              &byRsvTime);
    VNSvOutPortW(pDevice->PortOffset + MAC_REG_RSPINF_A_24, MAKEWORD(byTxRate,byRsvTime));
    //RSPINF_a_36
    s_vCaculateOFDMRParameter(
                              VNTWIFIbyGetACKTxRate(RATE_36M, pvSupportRateIEs, pvExtSupportRateIEs),
                              ePHYType,
                              &byTxRate,
                              &byRsvTime);
    VNSvOutPortW(pDevice->PortOffset + MAC_REG_RSPINF_A_36, MAKEWORD(byTxRate,byRsvTime));
    //RSPINF_a_48
    s_vCaculateOFDMRParameter(
                              VNTWIFIbyGetACKTxRate(RATE_48M, pvSupportRateIEs, pvExtSupportRateIEs),
                              ePHYType,
                              &byTxRate,
                              &byRsvTime);
    VNSvOutPortW(pDevice->PortOffset + MAC_REG_RSPINF_A_48, MAKEWORD(byTxRate,byRsvTime));
    //RSPINF_a_54
    s_vCaculateOFDMRParameter(
                              VNTWIFIbyGetACKTxRate(RATE_54M, pvSupportRateIEs, pvExtSupportRateIEs),
                              ePHYType,
                              &byTxRate,
                              &byRsvTime);
    VNSvOutPortW(pDevice->PortOffset + MAC_REG_RSPINF_A_54, MAKEWORD(byTxRate,byRsvTime));
    //RSPINF_a_72
    VNSvOutPortW(pDevice->PortOffset + MAC_REG_RSPINF_A_72, MAKEWORD(byTxRate,byRsvTime));
    //Set to Page0
    MACvSelectPage0(pDevice->PortOffset);
}