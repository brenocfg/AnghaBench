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
typedef  void* u32 ;
typedef  int u16 ;
struct wb35_reg {void* BB60; void* BB5C; void* BB58; void* BB54; void* BB50; void* BB4C; void* BB48; void* BB3C; void* BB30; void* BB2C; void* BB0C; void* M98_MacControl; void* M88_MacControl; void* M84_MacControl; void* M80_MacControl; void* M7C_MacControl; void* M78_ERPInformation; void* M74_MacControl; void* M70_MacControl; void* M68_MacControl; void* M60_MacControl; void* M4C_MacStatus; void* M48_MacControl; void* M44_MacControl; void* M40_MacControl; void* M38_MacControl; void* M2C_MacControl; void* M28_MacControl; void* M24_MacControl; void* M08_MulticastAddress2; void* M04_MulticastAddress1; void* M00_MacControl; void* D00_DmaControl; void* U1BC_LEDConfigure; void* U1B0; } ;
struct hw_data {struct wb35_reg reg; } ;

/* Variables and functions */

void
Wb35Reg_Update(struct hw_data * pHwData,  u16 RegisterNo,  u32 RegisterValue)
{
	struct wb35_reg *reg = &pHwData->reg;
	switch (RegisterNo) {
	case 0x3b0: reg->U1B0 = RegisterValue; break;
	case 0x3bc: reg->U1BC_LEDConfigure = RegisterValue; break;
	case 0x400: reg->D00_DmaControl = RegisterValue; break;
	case 0x800: reg->M00_MacControl = RegisterValue; break;
	case 0x804: reg->M04_MulticastAddress1 = RegisterValue; break;
	case 0x808: reg->M08_MulticastAddress2 = RegisterValue; break;
	case 0x824: reg->M24_MacControl = RegisterValue; break;
	case 0x828: reg->M28_MacControl = RegisterValue; break;
	case 0x82c: reg->M2C_MacControl = RegisterValue; break;
	case 0x838: reg->M38_MacControl = RegisterValue; break;
	case 0x840: reg->M40_MacControl = RegisterValue; break;
	case 0x844: reg->M44_MacControl = RegisterValue; break;
	case 0x848: reg->M48_MacControl = RegisterValue; break;
	case 0x84c: reg->M4C_MacStatus = RegisterValue; break;
	case 0x860: reg->M60_MacControl = RegisterValue; break;
	case 0x868: reg->M68_MacControl = RegisterValue; break;
	case 0x870: reg->M70_MacControl = RegisterValue; break;
	case 0x874: reg->M74_MacControl = RegisterValue; break;
	case 0x878: reg->M78_ERPInformation = RegisterValue; break;
	case 0x87C: reg->M7C_MacControl = RegisterValue; break;
	case 0x880: reg->M80_MacControl = RegisterValue; break;
	case 0x884: reg->M84_MacControl = RegisterValue; break;
	case 0x888: reg->M88_MacControl = RegisterValue; break;
	case 0x898: reg->M98_MacControl = RegisterValue; break;
	case 0x100c: reg->BB0C = RegisterValue; break;
	case 0x102c: reg->BB2C = RegisterValue; break;
	case 0x1030: reg->BB30 = RegisterValue; break;
	case 0x103c: reg->BB3C = RegisterValue; break;
	case 0x1048: reg->BB48 = RegisterValue; break;
	case 0x104c: reg->BB4C = RegisterValue; break;
	case 0x1050: reg->BB50 = RegisterValue; break;
	case 0x1054: reg->BB54 = RegisterValue; break;
	case 0x1058: reg->BB58 = RegisterValue; break;
	case 0x105c: reg->BB5C = RegisterValue; break;
	case 0x1060: reg->BB60 = RegisterValue; break;
	}
}