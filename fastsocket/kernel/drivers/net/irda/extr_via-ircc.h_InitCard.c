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
 int /*<<< orphan*/  I_ST_CT_0 ; 
 int /*<<< orphan*/  ResetChip (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  SetSIRBOF (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  SetSIREOF (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  WriteReg (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void InitCard(__u16 iobase)
{
	ResetChip(iobase, 5);
	WriteReg(iobase, I_ST_CT_0, 0x00);	// open CHIP on
	SetSIRBOF(iobase, 0xc0);	// hardware default value
	SetSIREOF(iobase, 0xc1);
}