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
typedef  int /*<<< orphan*/ * filter_pred_fn_t ;

/* Variables and functions */
 int OP_EQ ; 
 int OP_NE ; 
 int /*<<< orphan*/ * filter_pred_16 ; 
 int /*<<< orphan*/ * filter_pred_32 ; 
 int /*<<< orphan*/ * filter_pred_64 ; 
 int /*<<< orphan*/ * filter_pred_8 ; 
 int /*<<< orphan*/ * filter_pred_s16 ; 
 int /*<<< orphan*/ * filter_pred_s32 ; 
 int /*<<< orphan*/ * filter_pred_s64 ; 
 int /*<<< orphan*/ * filter_pred_s8 ; 
 int /*<<< orphan*/ * filter_pred_u16 ; 
 int /*<<< orphan*/ * filter_pred_u32 ; 
 int /*<<< orphan*/ * filter_pred_u64 ; 
 int /*<<< orphan*/ * filter_pred_u8 ; 

__attribute__((used)) static filter_pred_fn_t select_comparison_fn(int op, int field_size,
					     int field_is_signed)
{
	filter_pred_fn_t fn = NULL;

	switch (field_size) {
	case 8:
		if (op == OP_EQ || op == OP_NE)
			fn = filter_pred_64;
		else if (field_is_signed)
			fn = filter_pred_s64;
		else
			fn = filter_pred_u64;
		break;
	case 4:
		if (op == OP_EQ || op == OP_NE)
			fn = filter_pred_32;
		else if (field_is_signed)
			fn = filter_pred_s32;
		else
			fn = filter_pred_u32;
		break;
	case 2:
		if (op == OP_EQ || op == OP_NE)
			fn = filter_pred_16;
		else if (field_is_signed)
			fn = filter_pred_s16;
		else
			fn = filter_pred_u16;
		break;
	case 1:
		if (op == OP_EQ || op == OP_NE)
			fn = filter_pred_8;
		else if (field_is_signed)
			fn = filter_pred_s8;
		else
			fn = filter_pred_u8;
		break;
	}

	return fn;
}