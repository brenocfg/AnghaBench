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
struct i2c_client {int dummy; } ;
typedef  enum mt9m111_context { ____Placeholder_mt9m111_context } mt9m111_context ;

/* Variables and functions */
 int /*<<< orphan*/  CONTEXT_CONTROL ; 
 int HIGHPOWER ; 
 int MT9M111_CTXT_CTRL_CTRL2_B ; 
 int MT9M111_CTXT_CTRL_DEFECTCOR_B ; 
 int MT9M111_CTXT_CTRL_GAMMA_B ; 
 int MT9M111_CTXT_CTRL_HBLANK_SEL_B ; 
 int MT9M111_CTXT_CTRL_READ_MODE_B ; 
 int MT9M111_CTXT_CTRL_RESIZE_B ; 
 int MT9M111_CTXT_CTRL_RESTART ; 
 int MT9M111_CTXT_CTRL_VBLANK_SEL_B ; 
 int reg_write (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int mt9m111_set_context(struct i2c_client *client,
			       enum mt9m111_context ctxt)
{
	int valB = MT9M111_CTXT_CTRL_RESTART | MT9M111_CTXT_CTRL_DEFECTCOR_B
		| MT9M111_CTXT_CTRL_RESIZE_B | MT9M111_CTXT_CTRL_CTRL2_B
		| MT9M111_CTXT_CTRL_GAMMA_B | MT9M111_CTXT_CTRL_READ_MODE_B
		| MT9M111_CTXT_CTRL_VBLANK_SEL_B
		| MT9M111_CTXT_CTRL_HBLANK_SEL_B;
	int valA = MT9M111_CTXT_CTRL_RESTART;

	if (ctxt == HIGHPOWER)
		return reg_write(CONTEXT_CONTROL, valB);
	else
		return reg_write(CONTEXT_CONTROL, valA);
}