#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int segments; scalar_t__ segment_pending; scalar_t__ count; scalar_t__ write; scalar_t__ read; scalar_t__* length; int /*<<< orphan*/ ** data; } ;
typedef  TYPE_1__ diva_um_idi_data_queue_t ;

/* Variables and functions */
 int /*<<< orphan*/  diva_os_free (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

int diva_data_q_finit(diva_um_idi_data_queue_t * q)
{
	int i;

	for (i = 0; i < q->segments; i++) {
		if (q->data[i]) {
			diva_os_free(0, q->data[i]);
		}
		q->data[i] = NULL;
		q->length[i] = 0;
	}
	q->read = q->write = q->count = q->segment_pending = 0;

	return (0);
}