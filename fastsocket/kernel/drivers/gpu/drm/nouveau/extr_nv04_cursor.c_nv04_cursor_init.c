#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int /*<<< orphan*/  show; int /*<<< orphan*/  hide; int /*<<< orphan*/  set_pos; int /*<<< orphan*/  set_offset; } ;
struct nouveau_crtc {TYPE_1__ cursor; } ;

/* Variables and functions */
 int /*<<< orphan*/  nv04_cursor_hide ; 
 int /*<<< orphan*/  nv04_cursor_set_offset ; 
 int /*<<< orphan*/  nv04_cursor_set_pos ; 
 int /*<<< orphan*/  nv04_cursor_show ; 

int
nv04_cursor_init(struct nouveau_crtc *crtc)
{
	crtc->cursor.set_offset = nv04_cursor_set_offset;
	crtc->cursor.set_pos = nv04_cursor_set_pos;
	crtc->cursor.hide = nv04_cursor_hide;
	crtc->cursor.show = nv04_cursor_show;
	return 0;
}