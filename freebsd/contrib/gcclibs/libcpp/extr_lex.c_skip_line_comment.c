#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {TYPE_1__* line_table; TYPE_3__* buffer; } ;
typedef  TYPE_2__ cpp_reader ;
struct TYPE_8__ {char* cur; } ;
typedef  TYPE_3__ cpp_buffer ;
struct TYPE_6__ {unsigned int highest_line; } ;

/* Variables and functions */
 int /*<<< orphan*/  _cpp_process_line_notes (TYPE_2__*,int) ; 

__attribute__((used)) static int
skip_line_comment (cpp_reader *pfile)
{
  cpp_buffer *buffer = pfile->buffer;
  unsigned int orig_line = pfile->line_table->highest_line;

  while (*buffer->cur != '\n')
    buffer->cur++;

  _cpp_process_line_notes (pfile, true);
  return orig_line != pfile->line_table->highest_line;
}