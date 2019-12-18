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
struct assign_parm_data_one {scalar_t__ nominal_mode; int /*<<< orphan*/  passed_type; int /*<<< orphan*/  passed_mode; int /*<<< orphan*/  promoted_mode; int /*<<< orphan*/  entry_parm; } ;

/* Variables and functions */
 scalar_t__ BLKmode ; 
 scalar_t__ BLOCK_REG_PADDING (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 scalar_t__ BYTES_BIG_ENDIAN ; 
 scalar_t__ GET_CODE (int /*<<< orphan*/ ) ; 
 scalar_t__ GET_MODE_SIZE (int /*<<< orphan*/ ) ; 
 scalar_t__ PARALLEL ; 
 scalar_t__ REG_P (int /*<<< orphan*/ ) ; 
 scalar_t__ UNITS_PER_WORD ; 
 scalar_t__ downward ; 
 scalar_t__ upward ; 

__attribute__((used)) static bool
assign_parm_setup_block_p (struct assign_parm_data_one *data)
{
  if (data->nominal_mode == BLKmode)
    return true;
  if (GET_CODE (data->entry_parm) == PARALLEL)
    return true;

#ifdef BLOCK_REG_PADDING
  /* Only assign_parm_setup_block knows how to deal with register arguments
     that are padded at the least significant end.  */
  if (REG_P (data->entry_parm)
      && GET_MODE_SIZE (data->promoted_mode) < UNITS_PER_WORD
      && (BLOCK_REG_PADDING (data->passed_mode, data->passed_type, 1)
	  == (BYTES_BIG_ENDIAN ? upward : downward)))
    return true;
#endif

  return false;
}