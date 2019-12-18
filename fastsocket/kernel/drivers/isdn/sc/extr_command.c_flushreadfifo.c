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
struct TYPE_2__ {int /*<<< orphan*/ * ioport; } ;

/* Variables and functions */
 size_t FIFO_READ ; 
 size_t FIFO_STATUS ; 
 int RF_HAS_DATA ; 
 int inb (int /*<<< orphan*/ ) ; 
 TYPE_1__** sc_adapter ; 

void flushreadfifo (int card)
{
	while(inb(sc_adapter[card]->ioport[FIFO_STATUS]) & RF_HAS_DATA)
		inb(sc_adapter[card]->ioport[FIFO_READ]);
}