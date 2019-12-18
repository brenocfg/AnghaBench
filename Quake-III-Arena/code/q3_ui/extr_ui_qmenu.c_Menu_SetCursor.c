#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int cursor_prev; int cursor; scalar_t__* items; } ;
typedef  TYPE_1__ menuframework_s ;
struct TYPE_6__ {int flags; } ;
typedef  TYPE_2__ menucommon_s ;

/* Variables and functions */
 int /*<<< orphan*/  Menu_CursorMoved (TYPE_1__*) ; 
 int QMF_GRAYED ; 
 int QMF_INACTIVE ; 

void Menu_SetCursor( menuframework_s *m, int cursor )
{
	if (((menucommon_s*)(m->items[cursor]))->flags & (QMF_GRAYED|QMF_INACTIVE))
	{
		// cursor can't go there
		return;
	}

	m->cursor_prev = m->cursor;
	m->cursor      = cursor;

	Menu_CursorMoved( m );
}