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
struct TYPE_4__ {int /*<<< orphan*/  cur; } ;
struct TYPE_3__ {int /*<<< orphan*/  buffer; } ;
struct nouveau_channel {TYPE_2__ dma; TYPE_1__ push; } ;

/* Variables and functions */
 int /*<<< orphan*/  nouveau_bo_wr32 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static inline void
OUT_RING(struct nouveau_channel *chan, int data)
{
	nouveau_bo_wr32(chan->push.buffer, chan->dma.cur++, data);
}