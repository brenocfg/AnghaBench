#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {TYPE_2__* overlaid_buffer; int /*<<< orphan*/  saved_line_base; int /*<<< orphan*/  saved_rlimit; int /*<<< orphan*/  saved_cur; } ;
typedef  TYPE_1__ cpp_reader ;
struct TYPE_5__ {int need_line; int /*<<< orphan*/  line_base; int /*<<< orphan*/  rlimit; int /*<<< orphan*/  cur; } ;
typedef  TYPE_2__ cpp_buffer ;

/* Variables and functions */

void
_cpp_remove_overlay (cpp_reader *pfile)
{
  cpp_buffer *buffer = pfile->overlaid_buffer;

  buffer->cur = pfile->saved_cur;
  buffer->rlimit = pfile->saved_rlimit;
  buffer->line_base = pfile->saved_line_base;
  buffer->need_line = true;

  pfile->overlaid_buffer = NULL;
}