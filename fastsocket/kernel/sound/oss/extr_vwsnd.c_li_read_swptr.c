#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/  ctlval; TYPE_1__* desc; } ;
typedef  TYPE_2__ dma_chan_t ;
struct TYPE_4__ {unsigned long swptrmask; } ;

/* Variables and functions */
 int CHUNKS_TO_BYTES (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  UNSHIFT_FIELD (int /*<<< orphan*/ ,unsigned long const) ; 

__attribute__((used)) static __inline__ int li_read_swptr(dma_chan_t *chan)
{
	const unsigned long mask = chan->desc->swptrmask;

	return CHUNKS_TO_BYTES(UNSHIFT_FIELD(chan->ctlval, mask));
}