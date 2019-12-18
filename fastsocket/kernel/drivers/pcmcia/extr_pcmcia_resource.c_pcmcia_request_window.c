#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_8__ ;
typedef  struct TYPE_12__   TYPE_5__ ;
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_12__ {int map; int static_start; TYPE_8__* res; scalar_t__ card_start; int /*<<< orphan*/  flags; int /*<<< orphan*/  speed; } ;
struct TYPE_10__ {int index; TYPE_5__ ctl; struct pcmcia_socket* sock; struct pcmcia_device* handle; int /*<<< orphan*/  magic; } ;
typedef  TYPE_2__ window_t ;
typedef  TYPE_2__* window_handle_t ;
struct TYPE_11__ {int Attributes; int Size; int Base; int /*<<< orphan*/  AccessSpeed; } ;
typedef  TYPE_4__ win_req_t ;
typedef  int u_long ;
struct pcmcia_socket {int state; int map_size; int features; TYPE_1__* ops; TYPE_2__* win; } ;
struct pcmcia_device {int /*<<< orphan*/  _win; struct pcmcia_socket* socket; } ;
struct TYPE_13__ {int start; } ;
struct TYPE_9__ {scalar_t__ (* set_mem_map ) (struct pcmcia_socket*,TYPE_5__*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  CLIENT_WIN_REQ (int) ; 
 int EINVAL ; 
 int EIO ; 
 int ENODEV ; 
 int /*<<< orphan*/  MAP_16BIT ; 
 int /*<<< orphan*/  MAP_ACTIVE ; 
 int /*<<< orphan*/  MAP_ATTRIB ; 
 int /*<<< orphan*/  MAP_USE_WAIT ; 
 int MAX_WIN ; 
 int SOCKET_PRESENT ; 
 int SOCKET_WIN_REQ (int) ; 
 int SS_CAP_MEM_ALIGN ; 
 int SS_CAP_STATIC_MAP ; 
 int /*<<< orphan*/  WINDOW_MAGIC ; 
 int WIN_DATA_WIDTH_16 ; 
 int WIN_ENABLE ; 
 int WIN_MAP_BELOW_1MB ; 
 int WIN_MEMORY_TYPE ; 
 int WIN_PAGED ; 
 int WIN_SHARED ; 
 int WIN_STRICT_ALIGN ; 
 int WIN_USE_WAIT ; 
 int /*<<< orphan*/  ds_dbg (struct pcmcia_socket*,int /*<<< orphan*/ ,char*) ; 
 TYPE_8__* pcmcia_find_mem_region (int,int,int,int,struct pcmcia_socket*) ; 
 scalar_t__ stub1 (struct pcmcia_socket*,TYPE_5__*) ; 

int pcmcia_request_window(struct pcmcia_device **p_dev, win_req_t *req, window_handle_t *wh)
{
	struct pcmcia_socket *s = (*p_dev)->socket;
	window_t *win;
	u_long align;
	int w;

	if (!(s->state & SOCKET_PRESENT))
		return -ENODEV;
	if (req->Attributes & (WIN_PAGED | WIN_SHARED)) {
		ds_dbg(s, 0, "bad attribute setting for iomem region\n");
		return -EINVAL;
	}

	/* Window size defaults to smallest available */
	if (req->Size == 0)
		req->Size = s->map_size;
	align = (((s->features & SS_CAP_MEM_ALIGN) ||
		  (req->Attributes & WIN_STRICT_ALIGN)) ?
		 req->Size : s->map_size);
	if (req->Size & (s->map_size-1)) {
		ds_dbg(s, 0, "invalid map size\n");
		return -EINVAL;
	}
	if ((req->Base && (s->features & SS_CAP_STATIC_MAP)) ||
	    (req->Base & (align-1))) {
		ds_dbg(s, 0, "invalid base address\n");
		return -EINVAL;
	}
	if (req->Base)
		align = 0;

	/* Allocate system memory window */
	for (w = 0; w < MAX_WIN; w++)
		if (!(s->state & SOCKET_WIN_REQ(w))) break;
	if (w == MAX_WIN) {
		ds_dbg(s, 0, "all windows are used already\n");
		return -EINVAL;
	}

	win = &s->win[w];
	win->magic = WINDOW_MAGIC;
	win->index = w;
	win->handle = *p_dev;
	win->sock = s;

	if (!(s->features & SS_CAP_STATIC_MAP)) {
		win->ctl.res = pcmcia_find_mem_region(req->Base, req->Size, align,
						      (req->Attributes & WIN_MAP_BELOW_1MB), s);
		if (!win->ctl.res) {
			ds_dbg(s, 0, "allocating mem region failed\n");
			return -EINVAL;
		}
	}
	(*p_dev)->_win |= CLIENT_WIN_REQ(w);

	/* Configure the socket controller */
	win->ctl.map = w+1;
	win->ctl.flags = 0;
	win->ctl.speed = req->AccessSpeed;
	if (req->Attributes & WIN_MEMORY_TYPE)
		win->ctl.flags |= MAP_ATTRIB;
	if (req->Attributes & WIN_ENABLE)
		win->ctl.flags |= MAP_ACTIVE;
	if (req->Attributes & WIN_DATA_WIDTH_16)
		win->ctl.flags |= MAP_16BIT;
	if (req->Attributes & WIN_USE_WAIT)
		win->ctl.flags |= MAP_USE_WAIT;
	win->ctl.card_start = 0;
	if (s->ops->set_mem_map(s, &win->ctl) != 0) {
		ds_dbg(s, 0, "failed to set memory mapping\n");
		return -EIO;
	}
	s->state |= SOCKET_WIN_REQ(w);

	/* Return window handle */
	if (s->features & SS_CAP_STATIC_MAP) {
		req->Base = win->ctl.static_start;
	} else {
		req->Base = win->ctl.res->start;
	}
	*wh = win;

	return 0;
}