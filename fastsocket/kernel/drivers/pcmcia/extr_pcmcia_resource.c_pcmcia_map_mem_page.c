#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_2__* window_handle_t ;
struct pcmcia_socket {TYPE_1__* ops; } ;
struct TYPE_9__ {scalar_t__ Page; int /*<<< orphan*/  CardOffset; } ;
typedef  TYPE_3__ memreq_t ;
struct TYPE_10__ {int /*<<< orphan*/  card_start; } ;
struct TYPE_8__ {scalar_t__ magic; TYPE_4__ ctl; struct pcmcia_socket* sock; } ;
struct TYPE_7__ {scalar_t__ (* set_mem_map ) (struct pcmcia_socket*,TYPE_4__*) ;} ;

/* Variables and functions */
 int EINVAL ; 
 int EIO ; 
 scalar_t__ WINDOW_MAGIC ; 
 int /*<<< orphan*/  ds_dbg (struct pcmcia_socket*,int /*<<< orphan*/ ,char*) ; 
 scalar_t__ stub1 (struct pcmcia_socket*,TYPE_4__*) ; 

int pcmcia_map_mem_page(window_handle_t win, memreq_t *req)
{
	struct pcmcia_socket *s;
	if ((win == NULL) || (win->magic != WINDOW_MAGIC))
		return -EINVAL;
	s = win->sock;
	if (req->Page != 0) {
		ds_dbg(s, 0, "failure: requested page is zero\n");
		return -EINVAL;
	}
	win->ctl.card_start = req->CardOffset;
	if (s->ops->set_mem_map(s, &win->ctl) != 0) {
		ds_dbg(s, 0, "failed to set_mem_map\n");
		return -EIO;
	}
	return 0;
}