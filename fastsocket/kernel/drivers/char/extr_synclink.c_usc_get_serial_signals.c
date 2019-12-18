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
typedef  int u16 ;
struct mgsl_struct {int /*<<< orphan*/  serial_signals; } ;

/* Variables and functions */
 int MISCSTATUS_CTS ; 
 int MISCSTATUS_DCD ; 
 int MISCSTATUS_DSR ; 
 int MISCSTATUS_RI ; 
 int /*<<< orphan*/  MISR ; 
 int /*<<< orphan*/  SerialSignal_CTS ; 
 int /*<<< orphan*/  SerialSignal_DCD ; 
 int /*<<< orphan*/  SerialSignal_DSR ; 
 int /*<<< orphan*/  SerialSignal_DTR ; 
 int /*<<< orphan*/  SerialSignal_RI ; 
 int /*<<< orphan*/  SerialSignal_RTS ; 
 int usc_InReg (struct mgsl_struct*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void usc_get_serial_signals( struct mgsl_struct *info )
{
	u16 status;

	/* clear all serial signals except DTR and RTS */
	info->serial_signals &= SerialSignal_DTR + SerialSignal_RTS;

	/* Read the Misc Interrupt status Register (MISR) to get */
	/* the V24 status signals. */

	status = usc_InReg( info, MISR );

	/* set serial signal bits to reflect MISR */

	if ( status & MISCSTATUS_CTS )
		info->serial_signals |= SerialSignal_CTS;

	if ( status & MISCSTATUS_DCD )
		info->serial_signals |= SerialSignal_DCD;

	if ( status & MISCSTATUS_RI )
		info->serial_signals |= SerialSignal_RI;

	if ( status & MISCSTATUS_DSR )
		info->serial_signals |= SerialSignal_DSR;

}