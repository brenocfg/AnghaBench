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
typedef  TYPE_2__* window_handle_t ;
struct TYPE_8__ {int /*<<< orphan*/  CardOffset; scalar_t__ Page; } ;
typedef  TYPE_3__ memreq_t ;
struct TYPE_6__ {int /*<<< orphan*/  card_start; } ;
struct TYPE_7__ {scalar_t__ magic; TYPE_1__ ctl; } ;

/* Variables and functions */
 int EINVAL ; 
 scalar_t__ WINDOW_MAGIC ; 

int pcmcia_get_mem_page(window_handle_t win, memreq_t *req)
{
	if ((win == NULL) || (win->magic != WINDOW_MAGIC))
		return -EINVAL;
	req->Page = 0;
	req->CardOffset = win->ctl.card_start;
	return 0;
}