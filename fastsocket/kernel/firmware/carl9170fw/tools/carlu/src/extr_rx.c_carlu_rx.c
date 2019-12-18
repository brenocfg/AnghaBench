#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct frame {int /*<<< orphan*/  len; int /*<<< orphan*/  data; } ;
struct carlu {scalar_t__ rx_stream; } ;

/* Variables and functions */
 int /*<<< orphan*/  __carlu_rx (struct carlu*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  carlu_rx_stream (struct carlu*,struct frame*) ; 

void carlu_rx(struct carlu *ar, struct frame *frame)
{
	if (ar->rx_stream)
		carlu_rx_stream(ar, frame);
	else
		__carlu_rx(ar, frame->data, frame->len);
}