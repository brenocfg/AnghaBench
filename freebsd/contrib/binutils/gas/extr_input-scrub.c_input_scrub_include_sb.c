#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int len; char* ptr; } ;
typedef  TYPE_1__ sb ;
struct TYPE_7__ {int /*<<< orphan*/  logical_input_file; int /*<<< orphan*/  logical_input_line; } ;

/* Variables and functions */
 int /*<<< orphan*/  _ (char*) ; 
 int /*<<< orphan*/  as_fatal (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  from_sb ; 
 int from_sb_is_expansion ; 
 TYPE_3__* input_scrub_push (char*) ; 
 int /*<<< orphan*/  logical_input_file ; 
 int /*<<< orphan*/  logical_input_line ; 
 scalar_t__ macro_nest ; 
 scalar_t__ max_macro_nest ; 
 int /*<<< orphan*/  md_macro_start () ; 
 TYPE_3__* next_saved_file ; 
 int /*<<< orphan*/  sb_add_char (int /*<<< orphan*/ *,char) ; 
 int sb_index ; 
 int /*<<< orphan*/  sb_new (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sb_scrub_and_add_sb (int /*<<< orphan*/ *,TYPE_1__*) ; 

void
input_scrub_include_sb (sb *from, char *position, int is_expansion)
{
  if (macro_nest > max_macro_nest)
    as_fatal (_("macros nested too deeply"));
  ++macro_nest;

#ifdef md_macro_start
  if (is_expansion)
    {
      md_macro_start ();
    }
#endif

  next_saved_file = input_scrub_push (position);

  sb_new (&from_sb);
  from_sb_is_expansion = is_expansion;
  if (from->len >= 1 && from->ptr[0] != '\n')
    {
      /* Add the sentinel required by read.c.  */
      sb_add_char (&from_sb, '\n');
    }
  sb_scrub_and_add_sb (&from_sb, from);
  sb_index = 1;

  /* These variables are reset by input_scrub_push.  Restore them
     since we are, after all, still at the same point in the file.  */
  logical_input_line = next_saved_file->logical_input_line;
  logical_input_file = next_saved_file->logical_input_file;
}