#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uchar ;
struct TYPE_5__ {int notes_used; int notes_cap; TYPE_3__* notes; } ;
typedef  TYPE_1__ cpp_buffer ;
struct TYPE_6__ {unsigned int type; int /*<<< orphan*/  const* pos; } ;

/* Variables and functions */
 TYPE_3__* XRESIZEVEC (int /*<<< orphan*/ ,TYPE_3__*,int) ; 
 int /*<<< orphan*/  _cpp_line_note ; 

__attribute__((used)) static void
add_line_note (cpp_buffer *buffer, const uchar *pos, unsigned int type)
{
  if (buffer->notes_used == buffer->notes_cap)
    {
      buffer->notes_cap = buffer->notes_cap * 2 + 200;
      buffer->notes = XRESIZEVEC (_cpp_line_note, buffer->notes,
                                  buffer->notes_cap);
    }

  buffer->notes[buffer->notes_used].pos = pos;
  buffer->notes[buffer->notes_used].type = type;
  buffer->notes_used++;
}