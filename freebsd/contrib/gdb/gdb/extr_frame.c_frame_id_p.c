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
struct frame_id {scalar_t__ stack_addr; } ;

/* Variables and functions */
 int /*<<< orphan*/  fprint_frame_id (int /*<<< orphan*/ ,struct frame_id) ; 
 int /*<<< orphan*/  fprintf_unfiltered (int /*<<< orphan*/ ,char*,...) ; 
 scalar_t__ frame_debug ; 
 int /*<<< orphan*/  gdb_stdlog ; 

int
frame_id_p (struct frame_id l)
{
  int p;
  /* The .code can be NULL but the .stack cannot.  */
  p = (l.stack_addr != 0);
  if (frame_debug)
    {
      fprintf_unfiltered (gdb_stdlog, "{ frame_id_p (l=");
      fprint_frame_id (gdb_stdlog, l);
      fprintf_unfiltered (gdb_stdlog, ") -> %d }\n", p);
    }
  return p;
}