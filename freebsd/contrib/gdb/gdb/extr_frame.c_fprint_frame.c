#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct ui_file {int dummy; } ;
struct TYPE_6__ {int /*<<< orphan*/  value; scalar_t__ p; } ;
struct frame_info {TYPE_4__* next; TYPE_2__ this_id; int /*<<< orphan*/ * unwind; int /*<<< orphan*/  type; int /*<<< orphan*/  level; } ;
struct TYPE_7__ {int /*<<< orphan*/  addr; scalar_t__ p; } ;
struct TYPE_5__ {int /*<<< orphan*/  value; scalar_t__ p; } ;
struct TYPE_8__ {TYPE_3__ prev_func; TYPE_1__ prev_pc; } ;

/* Variables and functions */
 int /*<<< orphan*/  fprint_frame_id (struct ui_file*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fprint_frame_type (struct ui_file*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fprintf_unfiltered (struct ui_file*,char*,...) ; 
 int /*<<< orphan*/  gdb_print_host_address (int /*<<< orphan*/ *,struct ui_file*) ; 
 int /*<<< orphan*/  paddr_nz (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
fprint_frame (struct ui_file *file, struct frame_info *fi)
{
  if (fi == NULL)
    {
      fprintf_unfiltered (file, "<NULL frame>");
      return;
    }
  fprintf_unfiltered (file, "{");
  fprintf_unfiltered (file, "level=%d", fi->level);
  fprintf_unfiltered (file, ",");
  fprintf_unfiltered (file, "type=");
  fprint_frame_type (file, fi->type);
  fprintf_unfiltered (file, ",");
  fprintf_unfiltered (file, "unwind=");
  if (fi->unwind != NULL)
    gdb_print_host_address (fi->unwind, file);
  else
    fprintf_unfiltered (file, "<unknown>");
  fprintf_unfiltered (file, ",");
  fprintf_unfiltered (file, "pc=");
  if (fi->next != NULL && fi->next->prev_pc.p)
    fprintf_unfiltered (file, "0x%s", paddr_nz (fi->next->prev_pc.value));
  else
    fprintf_unfiltered (file, "<unknown>");
  fprintf_unfiltered (file, ",");
  fprintf_unfiltered (file, "id=");
  if (fi->this_id.p)
    fprint_frame_id (file, fi->this_id.value);
  else
    fprintf_unfiltered (file, "<unknown>");
  fprintf_unfiltered (file, ",");
  fprintf_unfiltered (file, "func=");
  if (fi->next != NULL && fi->next->prev_func.p)
    fprintf_unfiltered (file, "0x%s", paddr_nz (fi->next->prev_func.addr));
  else
    fprintf_unfiltered (file, "<unknown>");
  fprintf_unfiltered (file, "}");
}