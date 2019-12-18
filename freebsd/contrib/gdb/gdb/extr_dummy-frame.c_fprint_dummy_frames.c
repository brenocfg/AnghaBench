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
struct ui_file {int dummy; } ;
struct dummy_frame {int /*<<< orphan*/  call_hi; int /*<<< orphan*/  call_lo; int /*<<< orphan*/  id; int /*<<< orphan*/  top; int /*<<< orphan*/  sp; int /*<<< orphan*/  fp; int /*<<< orphan*/  pc; struct dummy_frame* next; } ;

/* Variables and functions */
 struct dummy_frame* dummy_frame_stack ; 
 int /*<<< orphan*/  fprint_frame_id (struct ui_file*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fprintf_unfiltered (struct ui_file*,char*,...) ; 
 int /*<<< orphan*/  gdb_print_host_address (struct dummy_frame*,struct ui_file*) ; 
 int /*<<< orphan*/  paddr (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
fprint_dummy_frames (struct ui_file *file)
{
  struct dummy_frame *s;
  for (s = dummy_frame_stack; s != NULL; s = s->next)
    {
      gdb_print_host_address (s, file);
      fprintf_unfiltered (file, ":");
      fprintf_unfiltered (file, " pc=0x%s", paddr (s->pc));
      fprintf_unfiltered (file, " fp=0x%s", paddr (s->fp));
      fprintf_unfiltered (file, " sp=0x%s", paddr (s->sp));
      fprintf_unfiltered (file, " top=0x%s", paddr (s->top));
      fprintf_unfiltered (file, " id=");
      fprint_frame_id (file, s->id);
      fprintf_unfiltered (file, " call_lo=0x%s", paddr (s->call_lo));
      fprintf_unfiltered (file, " call_hi=0x%s", paddr (s->call_hi));
      fprintf_unfiltered (file, "\n");
    }
}