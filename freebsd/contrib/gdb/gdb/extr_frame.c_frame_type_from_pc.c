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
typedef  enum frame_type { ____Placeholder_frame_type } frame_type ;
typedef  int /*<<< orphan*/  CORE_ADDR ;

/* Variables and functions */
 scalar_t__ DEPRECATED_PC_IN_CALL_DUMMY (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ DEPRECATED_USE_GENERIC_DUMMY_FRAMES ; 
 int DUMMY_FRAME ; 
 int NORMAL_FRAME ; 
 scalar_t__ PC_IN_SIGTRAMP (int /*<<< orphan*/ ,char*) ; 
 int SIGTRAMP_FRAME ; 
 int /*<<< orphan*/  find_pc_partial_function (int /*<<< orphan*/ ,char**,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static enum frame_type
frame_type_from_pc (CORE_ADDR pc)
{
  /* FIXME: cagney/2002-11-24: Can't yet directly call
     pc_in_dummy_frame() as some architectures don't set
     PC_IN_CALL_DUMMY() to generic_pc_in_call_dummy() (remember the
     latter is implemented by simply calling pc_in_dummy_frame).  */
  if (DEPRECATED_USE_GENERIC_DUMMY_FRAMES
      && DEPRECATED_PC_IN_CALL_DUMMY (pc, 0, 0))
    return DUMMY_FRAME;
  else
    {
      char *name;
      find_pc_partial_function (pc, &name, NULL, NULL);
      if (PC_IN_SIGTRAMP (pc, name))
	return SIGTRAMP_FRAME;
      else
	return NORMAL_FRAME;
    }
}