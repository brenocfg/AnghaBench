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
typedef  int /*<<< orphan*/  uchar ;
struct TYPE_4__ {int /*<<< orphan*/  saved_line_base; int /*<<< orphan*/  const* saved_rlimit; int /*<<< orphan*/  const* saved_cur; TYPE_2__* overlaid_buffer; TYPE_2__* buffer; } ;
typedef  TYPE_1__ cpp_reader ;
struct TYPE_5__ {int need_line; int /*<<< orphan*/  const* rlimit; int /*<<< orphan*/  const* line_base; int /*<<< orphan*/  const* cur; int /*<<< orphan*/  next_line; } ;
typedef  TYPE_2__ cpp_buffer ;

/* Variables and functions */

void
_cpp_overlay_buffer (cpp_reader *pfile, const uchar *start, size_t len)
{
  cpp_buffer *buffer = pfile->buffer;

  pfile->overlaid_buffer = buffer;
  pfile->saved_cur = buffer->cur;
  pfile->saved_rlimit = buffer->rlimit;
  pfile->saved_line_base = buffer->next_line;
  buffer->need_line = false;

  buffer->cur = start;
  buffer->line_base = start;
  buffer->rlimit = start + len;
}