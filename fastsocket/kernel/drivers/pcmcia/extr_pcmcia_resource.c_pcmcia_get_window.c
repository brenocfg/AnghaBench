#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_5__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {int flags; int /*<<< orphan*/  speed; TYPE_1__* res; } ;
struct TYPE_10__ {TYPE_2__ ctl; } ;
typedef  TYPE_3__ window_t ;
typedef  TYPE_3__* window_handle_t ;
struct TYPE_11__ {int /*<<< orphan*/  Attributes; int /*<<< orphan*/  AccessSpeed; scalar_t__ Size; scalar_t__ Base; } ;
typedef  TYPE_5__ win_req_t ;
struct pcmcia_socket {int state; TYPE_3__* win; } ;
struct TYPE_8__ {scalar_t__ start; scalar_t__ end; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENODEV ; 
 int MAP_16BIT ; 
 int MAP_ACTIVE ; 
 int MAP_ATTRIB ; 
 int MAP_USE_WAIT ; 
 int MAX_WIN ; 
 int SOCKET_PRESENT ; 
 int SOCKET_WIN_REQ (int) ; 
 int /*<<< orphan*/  WIN_DATA_WIDTH_16 ; 
 int /*<<< orphan*/  WIN_ENABLE ; 
 int /*<<< orphan*/  WIN_MEMORY_TYPE_AM ; 
 int /*<<< orphan*/  WIN_USE_WAIT ; 

int pcmcia_get_window(struct pcmcia_socket *s, window_handle_t *handle,
		      int idx, win_req_t *req)
{
	window_t *win;
	int w;

	if (!s || !(s->state & SOCKET_PRESENT))
		return -ENODEV;
	for (w = idx; w < MAX_WIN; w++)
		if (s->state & SOCKET_WIN_REQ(w))
			break;
	if (w == MAX_WIN)
		return -EINVAL;
	win = &s->win[w];
	req->Base = win->ctl.res->start;
	req->Size = win->ctl.res->end - win->ctl.res->start + 1;
	req->AccessSpeed = win->ctl.speed;
	req->Attributes = 0;
	if (win->ctl.flags & MAP_ATTRIB)
		req->Attributes |= WIN_MEMORY_TYPE_AM;
	if (win->ctl.flags & MAP_ACTIVE)
		req->Attributes |= WIN_ENABLE;
	if (win->ctl.flags & MAP_16BIT)
		req->Attributes |= WIN_DATA_WIDTH_16;
	if (win->ctl.flags & MAP_USE_WAIT)
		req->Attributes |= WIN_USE_WAIT;
	*handle = win;
	return 0;
}