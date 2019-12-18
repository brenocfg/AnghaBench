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
struct TYPE_4__ {int idle_mode; } ;
typedef  TYPE_1__ SLMP_INFO ;

/* Variables and functions */
#define  HDLC_TXIDLE_ALT_MARK_SPACE 134 
#define  HDLC_TXIDLE_ALT_ZEROS_ONES 133 
#define  HDLC_TXIDLE_FLAGS 132 
#define  HDLC_TXIDLE_MARK 131 
#define  HDLC_TXIDLE_ONES 130 
#define  HDLC_TXIDLE_SPACE 129 
#define  HDLC_TXIDLE_ZEROS 128 
 int /*<<< orphan*/  IDL ; 
 int /*<<< orphan*/  write_reg (TYPE_1__*,int /*<<< orphan*/ ,unsigned char) ; 

__attribute__((used)) static void tx_set_idle(SLMP_INFO *info)
{
	unsigned char RegValue = 0xff;

	/* Map API idle mode to SCA register bits */
	switch(info->idle_mode) {
	case HDLC_TXIDLE_FLAGS:			RegValue = 0x7e; break;
	case HDLC_TXIDLE_ALT_ZEROS_ONES:	RegValue = 0xaa; break;
	case HDLC_TXIDLE_ZEROS:			RegValue = 0x00; break;
	case HDLC_TXIDLE_ONES:			RegValue = 0xff; break;
	case HDLC_TXIDLE_ALT_MARK_SPACE:	RegValue = 0xaa; break;
	case HDLC_TXIDLE_SPACE:			RegValue = 0x00; break;
	case HDLC_TXIDLE_MARK:			RegValue = 0xff; break;
	}

	write_reg(info, IDL, RegValue);
}