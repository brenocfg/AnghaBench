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
typedef  int /*<<< orphan*/  irqreturn_t ;
typedef  int /*<<< orphan*/  avmcard ;

/* Variables and functions */
 int /*<<< orphan*/  c4_handle_interrupt (int /*<<< orphan*/ *) ; 

__attribute__((used)) static irqreturn_t c4_interrupt(int interrupt, void *devptr)
{
	avmcard *card = devptr;

	return c4_handle_interrupt(card);
}