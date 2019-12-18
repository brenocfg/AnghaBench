#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct sclp_buffer {scalar_t__ current_length; int /*<<< orphan*/ * current_line; TYPE_2__* sccb; } ;
struct mto {int dummy; } ;
struct TYPE_3__ {int length; } ;
struct TYPE_4__ {TYPE_1__ header; } ;

/* Variables and functions */
 int MAX_SCCB_ROOM ; 

int
sclp_buffer_space(struct sclp_buffer *buffer)
{
	int count;

	count = MAX_SCCB_ROOM - buffer->sccb->header.length;
	if (buffer->current_line != NULL)
		count -= sizeof(struct mto) + buffer->current_length;
	return count;
}