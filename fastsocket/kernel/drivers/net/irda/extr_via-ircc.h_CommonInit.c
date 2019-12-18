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
typedef  int /*<<< orphan*/  __u16 ;

/* Variables and functions */
 int /*<<< orphan*/  EnRXFIFOHalfLevelInt (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  EnRXFIFOReadyInt (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  EnRXSpecInt (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  EnTXFIFOHalfLevelInt (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  EnTXFIFOUnderrunEOMInt (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  EnableDMA (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  I_ST_CT_0 ; 
 int /*<<< orphan*/  InvertRX (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  InvertTX (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ IsSIROn (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  OFF ; 
 int /*<<< orphan*/  ON ; 
 int /*<<< orphan*/  SIRFilter (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SIRRecvAny (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SetMaxRxPacketSize (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  SwapDMA (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WriteReg (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void CommonInit(__u16 iobase)
{
//  EnTXCRC(iobase,0);
	SwapDMA(iobase, OFF);
	SetMaxRxPacketSize(iobase, 0x0fff);	//set to max:4095
	EnRXFIFOReadyInt(iobase, OFF);
	EnRXFIFOHalfLevelInt(iobase, OFF);
	EnTXFIFOHalfLevelInt(iobase, OFF);
	EnTXFIFOUnderrunEOMInt(iobase, ON);
//  EnTXFIFOReadyInt(iobase,ON);
	InvertTX(iobase, OFF);
	InvertRX(iobase, OFF);
//  WriteLPCReg(0xF0,0); //(if VT1211 then do this)
	if (IsSIROn(iobase)) {
		SIRFilter(iobase, ON);
		SIRRecvAny(iobase, ON);
	} else {
		SIRFilter(iobase, OFF);
		SIRRecvAny(iobase, OFF);
	}
	EnRXSpecInt(iobase, ON);
	WriteReg(iobase, I_ST_CT_0, 0x80);
	EnableDMA(iobase, ON);
}