#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_47__   TYPE_9__ ;
typedef  struct TYPE_46__   TYPE_8__ ;
typedef  struct TYPE_45__   TYPE_7__ ;
typedef  struct TYPE_44__   TYPE_6__ ;
typedef  struct TYPE_43__   TYPE_5__ ;
typedef  struct TYPE_42__   TYPE_4__ ;
typedef  struct TYPE_41__   TYPE_3__ ;
typedef  struct TYPE_40__   TYPE_2__ ;
typedef  struct TYPE_39__   TYPE_23__ ;
typedef  struct TYPE_38__   TYPE_22__ ;
typedef  struct TYPE_37__   TYPE_21__ ;
typedef  struct TYPE_36__   TYPE_20__ ;
typedef  struct TYPE_35__   TYPE_1__ ;
typedef  struct TYPE_34__   TYPE_19__ ;
typedef  struct TYPE_33__   TYPE_18__ ;
typedef  struct TYPE_32__   TYPE_17__ ;
typedef  struct TYPE_31__   TYPE_16__ ;
typedef  struct TYPE_30__   TYPE_15__ ;
typedef  struct TYPE_29__   TYPE_14__ ;
typedef  struct TYPE_28__   TYPE_13__ ;
typedef  struct TYPE_27__   TYPE_12__ ;
typedef  struct TYPE_26__   TYPE_11__ ;
typedef  struct TYPE_25__   TYPE_10__ ;

/* Type definitions */
struct TYPE_45__ {int reg; } ;
struct TYPE_44__ {int reg; } ;
struct TYPE_43__ {int reg; } ;
struct TYPE_42__ {int reg; } ;
struct TYPE_41__ {int reg; } ;
struct TYPE_46__ {TYPE_7__ cr4; TYPE_6__ cr3; TYPE_5__ cr2; TYPE_4__ cr1; TYPE_3__ cr0; } ;
struct TYPE_47__ {TYPE_8__ SOP; } ;
struct TYPE_35__ {scalar_t__* CallerID; } ;
struct TYPE_40__ {TYPE_1__ CAO; } ;
struct TYPE_36__ {int* IMFilterCoeff_1; int* IMFilterCoeff_2; int* FRXFilterCoeff; int* FRRFilterCoeff; int* AXFilterCoeff; int* ARFilterCoeff; int* THFilterCoeff_1; int* THFilterCoeff_2; int* THFilterCoeff_3; int* RingerImpendance_1; int* RingerImpendance_2; int* LevelmeteringRinging; int* CallerID1stTone; int* CallerID2ndTone; int* Tone1Coeff; int* Tone2Coeff; } ;
struct TYPE_37__ {TYPE_20__ COP; } ;
struct TYPE_32__ {int reg; } ;
struct TYPE_30__ {int reg; } ;
struct TYPE_29__ {int reg; } ;
struct TYPE_28__ {int reg; } ;
struct TYPE_27__ {int reg; } ;
struct TYPE_26__ {int reg; } ;
struct TYPE_33__ {TYPE_17__ xr7; TYPE_15__ xr5; TYPE_14__ xr4; TYPE_13__ xr3; TYPE_12__ xr2; TYPE_11__ xr1; } ;
struct TYPE_34__ {TYPE_18__ XOP; } ;
struct TYPE_31__ {int reg; } ;
struct TYPE_25__ {int reg; } ;
struct TYPE_38__ {TYPE_21__ COP_REGS; TYPE_19__ XOP_REGS; TYPE_16__ XOP_xr6_W; TYPE_10__ XOP_xr0_W; TYPE_9__ SOP_REGS; TYPE_2__ CAO_REGS; } ;
struct TYPE_39__ {TYPE_22__ m_DAAShadowRegs; int /*<<< orphan*/  daa_country; } ;
typedef  TYPE_23__ IXJ ;

/* Variables and functions */
 int ALISDAA_CALLERID_SIZE ; 
 int /*<<< orphan*/  DAA_US ; 

__attribute__((used)) static void DAA_Coeff_US(IXJ *j)
{
	int i;

	j->daa_country = DAA_US;
	/*----------------------------------------------- */
	/* CAO */
	for (i = 0; i < ALISDAA_CALLERID_SIZE; i++) {
		j->m_DAAShadowRegs.CAO_REGS.CAO.CallerID[i] = 0;
	}

/* Bytes for IM-filter part 1 (04): 0E,32,E2,2F,C2,5A,C0,00 */
	j->m_DAAShadowRegs.COP_REGS.COP.IMFilterCoeff_1[7] = 0x03;
	j->m_DAAShadowRegs.COP_REGS.COP.IMFilterCoeff_1[6] = 0x4B;
	j->m_DAAShadowRegs.COP_REGS.COP.IMFilterCoeff_1[5] = 0x5D;
	j->m_DAAShadowRegs.COP_REGS.COP.IMFilterCoeff_1[4] = 0xCD;
	j->m_DAAShadowRegs.COP_REGS.COP.IMFilterCoeff_1[3] = 0x24;
	j->m_DAAShadowRegs.COP_REGS.COP.IMFilterCoeff_1[2] = 0xC5;
	j->m_DAAShadowRegs.COP_REGS.COP.IMFilterCoeff_1[1] = 0xA0;
	j->m_DAAShadowRegs.COP_REGS.COP.IMFilterCoeff_1[0] = 0x00;
/* Bytes for IM-filter part 2 (05): 72,85,00,0E,2B,3A,D0,08 */
	j->m_DAAShadowRegs.COP_REGS.COP.IMFilterCoeff_2[7] = 0x71;
	j->m_DAAShadowRegs.COP_REGS.COP.IMFilterCoeff_2[6] = 0x1A;
	j->m_DAAShadowRegs.COP_REGS.COP.IMFilterCoeff_2[5] = 0x00;
	j->m_DAAShadowRegs.COP_REGS.COP.IMFilterCoeff_2[4] = 0x0A;
	j->m_DAAShadowRegs.COP_REGS.COP.IMFilterCoeff_2[3] = 0xB5;
	j->m_DAAShadowRegs.COP_REGS.COP.IMFilterCoeff_2[2] = 0x33;
	j->m_DAAShadowRegs.COP_REGS.COP.IMFilterCoeff_2[1] = 0xE0;
	j->m_DAAShadowRegs.COP_REGS.COP.IMFilterCoeff_2[0] = 0x08;
/* Bytes for FRX-filter       (08): 03,8F,48,F2,8F,48,70,08 */
	j->m_DAAShadowRegs.COP_REGS.COP.FRXFilterCoeff[7] = 0x05;
	j->m_DAAShadowRegs.COP_REGS.COP.FRXFilterCoeff[6] = 0xA3;
	j->m_DAAShadowRegs.COP_REGS.COP.FRXFilterCoeff[5] = 0x72;
	j->m_DAAShadowRegs.COP_REGS.COP.FRXFilterCoeff[4] = 0x34;
	j->m_DAAShadowRegs.COP_REGS.COP.FRXFilterCoeff[3] = 0x3F;
	j->m_DAAShadowRegs.COP_REGS.COP.FRXFilterCoeff[2] = 0x3B;
	j->m_DAAShadowRegs.COP_REGS.COP.FRXFilterCoeff[1] = 0x30;
	j->m_DAAShadowRegs.COP_REGS.COP.FRXFilterCoeff[0] = 0x08;
/* Bytes for FRR-filter       (07): 04,8F,38,7F,9B,EA,B0,08 */
	j->m_DAAShadowRegs.COP_REGS.COP.FRRFilterCoeff[7] = 0x05;
	j->m_DAAShadowRegs.COP_REGS.COP.FRRFilterCoeff[6] = 0x87;
	j->m_DAAShadowRegs.COP_REGS.COP.FRRFilterCoeff[5] = 0xF9;
	j->m_DAAShadowRegs.COP_REGS.COP.FRRFilterCoeff[4] = 0x3E;
	j->m_DAAShadowRegs.COP_REGS.COP.FRRFilterCoeff[3] = 0x32;
	j->m_DAAShadowRegs.COP_REGS.COP.FRRFilterCoeff[2] = 0xDA;
	j->m_DAAShadowRegs.COP_REGS.COP.FRRFilterCoeff[1] = 0xB0;
	j->m_DAAShadowRegs.COP_REGS.COP.FRRFilterCoeff[0] = 0x08;
/* Bytes for AX-filter        (0A): 16,55,DD,CA */
	j->m_DAAShadowRegs.COP_REGS.COP.AXFilterCoeff[3] = 0x41;
	j->m_DAAShadowRegs.COP_REGS.COP.AXFilterCoeff[2] = 0xB5;
	j->m_DAAShadowRegs.COP_REGS.COP.AXFilterCoeff[1] = 0xDD;
	j->m_DAAShadowRegs.COP_REGS.COP.AXFilterCoeff[0] = 0xCA;
/* Bytes for AR-filter        (09): 52,D3,11,42 */
	j->m_DAAShadowRegs.COP_REGS.COP.ARFilterCoeff[3] = 0x25;
	j->m_DAAShadowRegs.COP_REGS.COP.ARFilterCoeff[2] = 0xC7;
	j->m_DAAShadowRegs.COP_REGS.COP.ARFilterCoeff[1] = 0x10;
	j->m_DAAShadowRegs.COP_REGS.COP.ARFilterCoeff[0] = 0xD6;
/* Bytes for TH-filter part 1 (00): 00,42,48,81,B3,80,00,98 */
	j->m_DAAShadowRegs.COP_REGS.COP.THFilterCoeff_1[7] = 0x00;
	j->m_DAAShadowRegs.COP_REGS.COP.THFilterCoeff_1[6] = 0x42;
	j->m_DAAShadowRegs.COP_REGS.COP.THFilterCoeff_1[5] = 0x48;
	j->m_DAAShadowRegs.COP_REGS.COP.THFilterCoeff_1[4] = 0x81;
	j->m_DAAShadowRegs.COP_REGS.COP.THFilterCoeff_1[3] = 0xA5;
	j->m_DAAShadowRegs.COP_REGS.COP.THFilterCoeff_1[2] = 0x80;
	j->m_DAAShadowRegs.COP_REGS.COP.THFilterCoeff_1[1] = 0x00;
	j->m_DAAShadowRegs.COP_REGS.COP.THFilterCoeff_1[0] = 0x98;
/* Bytes for TH-filter part 2 (01): 02,F2,33,A0,68,AB,8A,AD */
	j->m_DAAShadowRegs.COP_REGS.COP.THFilterCoeff_2[7] = 0x02;
	j->m_DAAShadowRegs.COP_REGS.COP.THFilterCoeff_2[6] = 0xA2;
	j->m_DAAShadowRegs.COP_REGS.COP.THFilterCoeff_2[5] = 0x2B;
	j->m_DAAShadowRegs.COP_REGS.COP.THFilterCoeff_2[4] = 0xB0;
	j->m_DAAShadowRegs.COP_REGS.COP.THFilterCoeff_2[3] = 0xE8;
	j->m_DAAShadowRegs.COP_REGS.COP.THFilterCoeff_2[2] = 0xAB;
	j->m_DAAShadowRegs.COP_REGS.COP.THFilterCoeff_2[1] = 0x81;
	j->m_DAAShadowRegs.COP_REGS.COP.THFilterCoeff_2[0] = 0xCC;
/* Bytes for TH-filter part 3 (02): 00,88,DA,54,A4,BA,2D,BB */
	j->m_DAAShadowRegs.COP_REGS.COP.THFilterCoeff_3[7] = 0x00;
	j->m_DAAShadowRegs.COP_REGS.COP.THFilterCoeff_3[6] = 0x88;
	j->m_DAAShadowRegs.COP_REGS.COP.THFilterCoeff_3[5] = 0xD2;
	j->m_DAAShadowRegs.COP_REGS.COP.THFilterCoeff_3[4] = 0x24;
	j->m_DAAShadowRegs.COP_REGS.COP.THFilterCoeff_3[3] = 0xBA;
	j->m_DAAShadowRegs.COP_REGS.COP.THFilterCoeff_3[2] = 0xA9;
	j->m_DAAShadowRegs.COP_REGS.COP.THFilterCoeff_3[1] = 0x3B;
	j->m_DAAShadowRegs.COP_REGS.COP.THFilterCoeff_3[0] = 0xA6;
/* ;  (10K, 0.68uF) */
	/*  */
	/* Bytes for Ringing part 1 (03):1B,3B,9B,BA,D4,1C,B3,23 */
	j->m_DAAShadowRegs.COP_REGS.COP.RingerImpendance_1[7] = 0x1B;
	j->m_DAAShadowRegs.COP_REGS.COP.RingerImpendance_1[6] = 0x3C;
	j->m_DAAShadowRegs.COP_REGS.COP.RingerImpendance_1[5] = 0x93;
	j->m_DAAShadowRegs.COP_REGS.COP.RingerImpendance_1[4] = 0x3A;
	j->m_DAAShadowRegs.COP_REGS.COP.RingerImpendance_1[3] = 0x22;
	j->m_DAAShadowRegs.COP_REGS.COP.RingerImpendance_1[2] = 0x12;
	j->m_DAAShadowRegs.COP_REGS.COP.RingerImpendance_1[1] = 0xA3;
	j->m_DAAShadowRegs.COP_REGS.COP.RingerImpendance_1[0] = 0x23;
	/* Bytes for Ringing part 2 (06):13,42,A6,BA,D4,73,CA,D5 */
	j->m_DAAShadowRegs.COP_REGS.COP.RingerImpendance_2[7] = 0x12;
	j->m_DAAShadowRegs.COP_REGS.COP.RingerImpendance_2[6] = 0xA2;
	j->m_DAAShadowRegs.COP_REGS.COP.RingerImpendance_2[5] = 0xA6;
	j->m_DAAShadowRegs.COP_REGS.COP.RingerImpendance_2[4] = 0xBA;
	j->m_DAAShadowRegs.COP_REGS.COP.RingerImpendance_2[3] = 0x22;
	j->m_DAAShadowRegs.COP_REGS.COP.RingerImpendance_2[2] = 0x7A;
	j->m_DAAShadowRegs.COP_REGS.COP.RingerImpendance_2[1] = 0x0A;
	j->m_DAAShadowRegs.COP_REGS.COP.RingerImpendance_2[0] = 0xD5;

	/* Levelmetering Ringing        (0D):B2,45,0F,8E       */
	j->m_DAAShadowRegs.COP_REGS.COP.LevelmeteringRinging[3] = 0xAA;
	j->m_DAAShadowRegs.COP_REGS.COP.LevelmeteringRinging[2] = 0x35;
	j->m_DAAShadowRegs.COP_REGS.COP.LevelmeteringRinging[1] = 0x0F;
	j->m_DAAShadowRegs.COP_REGS.COP.LevelmeteringRinging[0] = 0x8E;

	/* Bytes for Ringing part 1 (03):1B,3B,9B,BA,D4,1C,B3,23 */
/*	j->m_DAAShadowRegs.COP_REGS.COP.RingerImpendance_1[7] = 0x1C; */
/*	j->m_DAAShadowRegs.COP_REGS.COP.RingerImpendance_1[6] = 0xB3; */
/*	j->m_DAAShadowRegs.COP_REGS.COP.RingerImpendance_1[5] = 0xAB; */
/*	j->m_DAAShadowRegs.COP_REGS.COP.RingerImpendance_1[4] = 0xAB; */
/*	j->m_DAAShadowRegs.COP_REGS.COP.RingerImpendance_1[3] = 0x54; */
/*	j->m_DAAShadowRegs.COP_REGS.COP.RingerImpendance_1[2] = 0x2D; */
/*	j->m_DAAShadowRegs.COP_REGS.COP.RingerImpendance_1[1] = 0x62; */
/*	j->m_DAAShadowRegs.COP_REGS.COP.RingerImpendance_1[0] = 0x2D; */
	/* Bytes for Ringing part 2 (06):13,42,A6,BA,D4,73,CA,D5 */ 
/*	j->m_DAAShadowRegs.COP_REGS.COP.RingerImpendance_2[7] = 0x2D; */
/*	j->m_DAAShadowRegs.COP_REGS.COP.RingerImpendance_2[6] = 0x62; */
/*	j->m_DAAShadowRegs.COP_REGS.COP.RingerImpendance_2[5] = 0xA6; */
/*	j->m_DAAShadowRegs.COP_REGS.COP.RingerImpendance_2[4] = 0xBB; */
/*	j->m_DAAShadowRegs.COP_REGS.COP.RingerImpendance_2[3] = 0x2A; */
/*	j->m_DAAShadowRegs.COP_REGS.COP.RingerImpendance_2[2] = 0x7D; */
/*	j->m_DAAShadowRegs.COP_REGS.COP.RingerImpendance_2[1] = 0x0A; */
/*	j->m_DAAShadowRegs.COP_REGS.COP.RingerImpendance_2[0] = 0xD4; */
/* */
	/* Levelmetering Ringing        (0D):B2,45,0F,8E       */
/*	j->m_DAAShadowRegs.COP_REGS.COP.LevelmeteringRinging[3] = 0xAA; */
/*	j->m_DAAShadowRegs.COP_REGS.COP.LevelmeteringRinging[2] = 0x05; */
/*	j->m_DAAShadowRegs.COP_REGS.COP.LevelmeteringRinging[1] = 0x0F; */
/*	j->m_DAAShadowRegs.COP_REGS.COP.LevelmeteringRinging[0] = 0x8E; */

	/* Caller ID 1st Tone           (0E):CA,0E,CA,09,99,99,99,99 */
	j->m_DAAShadowRegs.COP_REGS.COP.CallerID1stTone[7] = 0xCA;
	j->m_DAAShadowRegs.COP_REGS.COP.CallerID1stTone[6] = 0x0E;
	j->m_DAAShadowRegs.COP_REGS.COP.CallerID1stTone[5] = 0xCA;
	j->m_DAAShadowRegs.COP_REGS.COP.CallerID1stTone[4] = 0x09;
	j->m_DAAShadowRegs.COP_REGS.COP.CallerID1stTone[3] = 0x99;
	j->m_DAAShadowRegs.COP_REGS.COP.CallerID1stTone[2] = 0x99;
	j->m_DAAShadowRegs.COP_REGS.COP.CallerID1stTone[1] = 0x99;
	j->m_DAAShadowRegs.COP_REGS.COP.CallerID1stTone[0] = 0x99;
/* Caller ID 2nd Tone           (0F):FD,B5,BA,07,DA,00,00,00 */
	j->m_DAAShadowRegs.COP_REGS.COP.CallerID2ndTone[7] = 0xFD;
	j->m_DAAShadowRegs.COP_REGS.COP.CallerID2ndTone[6] = 0xB5;
	j->m_DAAShadowRegs.COP_REGS.COP.CallerID2ndTone[5] = 0xBA;
	j->m_DAAShadowRegs.COP_REGS.COP.CallerID2ndTone[4] = 0x07;
	j->m_DAAShadowRegs.COP_REGS.COP.CallerID2ndTone[3] = 0xDA;
	j->m_DAAShadowRegs.COP_REGS.COP.CallerID2ndTone[2] = 0x00;
	j->m_DAAShadowRegs.COP_REGS.COP.CallerID2ndTone[1] = 0x00;
	j->m_DAAShadowRegs.COP_REGS.COP.CallerID2ndTone[0] = 0x00;
/*  */
	/* ;CR Registers */
	/* Config. Reg. 0 (filters)       (cr0):FE ; CLK gen. by crystal */
	j->m_DAAShadowRegs.SOP_REGS.SOP.cr0.reg = 0xFF;
/* Config. Reg. 1 (dialing)       (cr1):05 */
	j->m_DAAShadowRegs.SOP_REGS.SOP.cr1.reg = 0x05;
/* Config. Reg. 2 (caller ID)     (cr2):04 */
	j->m_DAAShadowRegs.SOP_REGS.SOP.cr2.reg = 0x04;
/* Config. Reg. 3 (testloops)     (cr3):03 ; SEL Bit==0, HP-disabled */
	j->m_DAAShadowRegs.SOP_REGS.SOP.cr3.reg = 0x00;
/* Config. Reg. 4 (analog gain)   (cr4):02 */
	j->m_DAAShadowRegs.SOP_REGS.SOP.cr4.reg = 0x02;
	/* Config. Reg. 5 (Version)       (cr5):02 */
	/* Config. Reg. 6 (Reserved)      (cr6):00 */
	/* Config. Reg. 7 (Reserved)      (cr7):00 */
	/*  */
	/* ;xr Registers */
	/* Ext. Reg. 0 (Interrupt Reg.)   (xr0):02 */

	j->m_DAAShadowRegs.XOP_xr0_W.reg = 0x02;	/* SO_1 set to '1' because it is inverted. */
	/* Ext. Reg. 1 (Interrupt enable) (xr1):3C Cadence, RING, Caller ID, VDD_OK */

	j->m_DAAShadowRegs.XOP_REGS.XOP.xr1.reg = 0x3C;
/* Ext. Reg. 2 (Cadence Time Out) (xr2):7D */
	j->m_DAAShadowRegs.XOP_REGS.XOP.xr2.reg = 0x7D;
/* Ext. Reg. 3 (DC Char)          (xr3):32 ; B-Filter Off == 1 */
	j->m_DAAShadowRegs.XOP_REGS.XOP.xr3.reg = 0x3B;		/*0x32; */
	/* Ext. Reg. 4 (Cadence)          (xr4):00 */

	j->m_DAAShadowRegs.XOP_REGS.XOP.xr4.reg = 0x00;
/* Ext. Reg. 5 (Ring timer)       (xr5):22 */
	j->m_DAAShadowRegs.XOP_REGS.XOP.xr5.reg = 0x22;
/* Ext. Reg. 6 (Power State)      (xr6):00 */
	j->m_DAAShadowRegs.XOP_xr6_W.reg = 0x00;
/* Ext. Reg. 7 (Vdd)              (xr7):40 */
	j->m_DAAShadowRegs.XOP_REGS.XOP.xr7.reg = 0x40;		/* 0x40 ??? Should it be 0x00? */
	/*  */
	/* DTMF Tone 1                     (0B): 11,B3,5A,2C ;   697 Hz   */
	/*                                       12,33,5A,C3 ;  770 Hz   */
	/*                                       13,3C,5B,32 ;  852 Hz   */
	/*                                       1D,1B,5C,CC ;  941 Hz   */

	j->m_DAAShadowRegs.COP_REGS.COP.Tone1Coeff[3] = 0x11;
	j->m_DAAShadowRegs.COP_REGS.COP.Tone1Coeff[2] = 0xB3;
	j->m_DAAShadowRegs.COP_REGS.COP.Tone1Coeff[1] = 0x5A;
	j->m_DAAShadowRegs.COP_REGS.COP.Tone1Coeff[0] = 0x2C;
/* DTMF Tone 2                     (0C): 32,32,52,B3 ;  1209 Hz   */
	/*                                       EC,1D,52,22 ;  1336 Hz   */
	/*                                       AA,AC,51,D2 ;  1477 Hz   */
	/*                                       9B,3B,51,25 ;  1633 Hz   */
	j->m_DAAShadowRegs.COP_REGS.COP.Tone2Coeff[3] = 0x32;
	j->m_DAAShadowRegs.COP_REGS.COP.Tone2Coeff[2] = 0x32;
	j->m_DAAShadowRegs.COP_REGS.COP.Tone2Coeff[1] = 0x52;
	j->m_DAAShadowRegs.COP_REGS.COP.Tone2Coeff[0] = 0xB3;
}