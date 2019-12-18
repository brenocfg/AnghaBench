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
struct frame_id {scalar_t__ stack_addr; scalar_t__ code_addr; scalar_t__ special_addr; } ;

/* Variables and functions */
 int /*<<< orphan*/  fprint_frame_id (int /*<<< orphan*/ ,struct frame_id) ; 
 int /*<<< orphan*/  fprintf_unfiltered (int /*<<< orphan*/ ,char*,...) ; 
 scalar_t__ frame_debug ; 
 int /*<<< orphan*/  gdb_stdlog ; 

int
frame_id_eq (struct frame_id l, struct frame_id r)
{
  int eq;
  if (l.stack_addr == 0 || r.stack_addr == 0)
    /* Like a NaN, if either ID is invalid, the result is false.  */
    eq = 0;
  else if (l.stack_addr != r.stack_addr)
    /* If .stack addresses are different, the frames are different.  */
    eq = 0;
  else if (l.code_addr == 0 || r.code_addr == 0)
    /* A zero code addr is a wild card, always succeed.  */
    eq = 1;
  else if (l.code_addr != r.code_addr)
    /* If .code addresses are different, the frames are different.  */
    eq = 0;
  else if (l.special_addr == 0 || r.special_addr == 0)
    /* A zero special addr is a wild card (or unused), always succeed.  */
    eq = 1;
  else if (l.special_addr == r.special_addr)
    /* Frames are equal.  */
    eq = 1;
  else
    /* No luck.  */
    eq = 0;
  if (frame_debug)
    {
      fprintf_unfiltered (gdb_stdlog, "{ frame_id_eq (l=");
      fprint_frame_id (gdb_stdlog, l);
      fprintf_unfiltered (gdb_stdlog, ",r=");
      fprint_frame_id (gdb_stdlog, r);
      fprintf_unfiltered (gdb_stdlog, ") -> %d }\n", eq);
    }
  return eq;
}