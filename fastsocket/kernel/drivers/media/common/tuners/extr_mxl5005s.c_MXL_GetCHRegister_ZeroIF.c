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
typedef  int u8 ;
typedef  int /*<<< orphan*/  u16 ;
struct dvb_frontend {int dummy; } ;

/* Variables and functions */
 int ARRAY_SIZE (int*) ; 
 scalar_t__ MXL_RegRead (struct dvb_frontend*,int,int*) ; 

__attribute__((used)) static u16 MXL_GetCHRegister_ZeroIF(struct dvb_frontend *fe, u8 *RegNum,
	u8 *RegVal, int *count)
{
	u16 status = 0;
	int i;

	u8 RegAddr[] = {43, 136};

	*count = ARRAY_SIZE(RegAddr);

	for (i = 0; i < *count; i++) {
		RegNum[i] = RegAddr[i];
		status += MXL_RegRead(fe, RegNum[i], &RegVal[i]);
	}

	return status;
}