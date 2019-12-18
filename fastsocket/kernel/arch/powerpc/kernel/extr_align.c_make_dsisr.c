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

/* Variables and functions */
 scalar_t__ IS_DSFORM (unsigned int) ; 
 scalar_t__ IS_XFORM (unsigned int) ; 

__attribute__((used)) static inline unsigned make_dsisr(unsigned instr)
{
	unsigned dsisr;


	/* bits  6:15 --> 22:31 */
	dsisr = (instr & 0x03ff0000) >> 16;

	if (IS_XFORM(instr)) {
		/* bits 29:30 --> 15:16 */
		dsisr |= (instr & 0x00000006) << 14;
		/* bit     25 -->    17 */
		dsisr |= (instr & 0x00000040) << 8;
		/* bits 21:24 --> 18:21 */
		dsisr |= (instr & 0x00000780) << 3;
	} else {
		/* bit      5 -->    17 */
		dsisr |= (instr & 0x04000000) >> 12;
		/* bits  1: 4 --> 18:21 */
		dsisr |= (instr & 0x78000000) >> 17;
		/* bits 30:31 --> 12:13 */
		if (IS_DSFORM(instr))
			dsisr |= (instr & 0x00000003) << 18;
	}

	return dsisr;
}