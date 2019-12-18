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
typedef  int /*<<< orphan*/  u8 ;
typedef  scalar_t__ u32 ;
struct TYPE_5__ {int /*<<< orphan*/  list; scalar_t__ send; scalar_t__ length; int /*<<< orphan*/ * buf; } ;
typedef  TYPE_1__ rndis_resp_t ;
struct TYPE_6__ {int /*<<< orphan*/  resp_queue; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_ATOMIC ; 
 TYPE_1__* kmalloc (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 TYPE_2__* rndis_per_dev_params ; 

__attribute__((used)) static rndis_resp_t *rndis_add_response (int configNr, u32 length)
{
	rndis_resp_t	*r;

	/* NOTE:  this gets copied into ether.c USB_BUFSIZ bytes ... */
	r = kmalloc (sizeof (rndis_resp_t) + length, GFP_ATOMIC);
	if (!r) return NULL;

	r->buf = (u8 *) (r + 1);
	r->length = length;
	r->send = 0;

	list_add_tail (&r->list,
		&(rndis_per_dev_params [configNr].resp_queue));
	return r;
}