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
typedef  int /*<<< orphan*/  u32 ;
typedef  int /*<<< orphan*/  u16 ;
struct dvb_frontend {int dummy; } ;

/* Variables and functions */
 scalar_t__ MXL_ControlWrite_Group (struct dvb_frontend*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static u16 MXL_ControlWrite(struct dvb_frontend *fe, u16 ControlNum, u32 value)
{
	u16 status = 0;

	/* Will write ALL Matching Control Name */
	/* Write Matching INIT Control */
	status += MXL_ControlWrite_Group(fe, ControlNum, value, 1);
	/* Write Matching CH Control */
	status += MXL_ControlWrite_Group(fe, ControlNum, value, 2);
#ifdef _MXL_INTERNAL
	/* Write Matching MXL Control */
	status += MXL_ControlWrite_Group(fe, ControlNum, value, 3);
#endif
	return status;
}