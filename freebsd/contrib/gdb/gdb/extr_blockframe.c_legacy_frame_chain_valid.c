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
struct frame_info {int dummy; } ;
typedef  scalar_t__ CORE_ADDR ;

/* Variables and functions */
 int DEPRECATED_FRAME_CHAIN_VALID (scalar_t__,struct frame_info*) ; 
 scalar_t__ DEPRECATED_FRAME_CHAIN_VALID_P () ; 
 scalar_t__ DEPRECATED_PC_IN_CALL_DUMMY (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ DEPRECATED_USE_GENERIC_DUMMY_FRAMES ; 
 scalar_t__ INNER_THAN (scalar_t__,int /*<<< orphan*/ ) ; 
 scalar_t__ deprecated_inside_entry_file (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  frame_pc_unwind (struct frame_info*) ; 
 int /*<<< orphan*/  get_frame_base (struct frame_info*) ; 
 int /*<<< orphan*/  get_frame_pc (struct frame_info*) ; 
 scalar_t__ legacy_inside_entry_func (int /*<<< orphan*/ ) ; 

int
legacy_frame_chain_valid (CORE_ADDR fp, struct frame_info *fi)
{
  /* Don't prune CALL_DUMMY frames.  */
  if (DEPRECATED_USE_GENERIC_DUMMY_FRAMES
      && DEPRECATED_PC_IN_CALL_DUMMY (get_frame_pc (fi), 0, 0))
    return 1;

  /* If the new frame pointer is zero, then it isn't valid.  */
  if (fp == 0)
    return 0;
  
  /* If the new frame would be inside (younger than) the previous frame,
     then it isn't valid.  */
  if (INNER_THAN (fp, get_frame_base (fi)))
    return 0;
  
  /* If the architecture has a custom DEPRECATED_FRAME_CHAIN_VALID,
     call it now.  */
  if (DEPRECATED_FRAME_CHAIN_VALID_P ())
    return DEPRECATED_FRAME_CHAIN_VALID (fp, fi);

  /* If we're already inside the entry function for the main objfile, then it
     isn't valid.  */
  if (legacy_inside_entry_func (get_frame_pc (fi)))
    return 0;

  /* If we're inside the entry file, it isn't valid.  */
  /* NOTE/drow 2002-12-25: should there be a way to disable this check?  It
     assumes a single small entry file, and the way some debug readers (e.g.
     dbxread) figure out which object is the entry file is somewhat hokey.  */
  if (deprecated_inside_entry_file (frame_pc_unwind (fi)))
      return 0;

  return 1;
}