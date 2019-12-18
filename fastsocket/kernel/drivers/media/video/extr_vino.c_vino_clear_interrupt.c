#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct vino_channel_settings {scalar_t__ channel; } ;
struct sgi_vino_channel {int /*<<< orphan*/  next_4_desc; int /*<<< orphan*/  start_desc_tbl; scalar_t__ line_count; scalar_t__ page_index; } ;
struct TYPE_6__ {struct sgi_vino_channel b; struct sgi_vino_channel a; } ;
struct TYPE_4__ {int /*<<< orphan*/  dma; } ;
struct TYPE_5__ {TYPE_1__ dummy_desc_table; } ;

/* Variables and functions */
 scalar_t__ VINO_CHANNEL_A ; 
 int /*<<< orphan*/  VINO_DESC_FETCH_DELAY ; 
 int /*<<< orphan*/  dprintk (char*,char) ; 
 int /*<<< orphan*/  udelay (int /*<<< orphan*/ ) ; 
 TYPE_3__* vino ; 
 TYPE_2__* vino_drvdata ; 

__attribute__((used)) static void vino_clear_interrupt(struct vino_channel_settings *vcs)
{
	struct sgi_vino_channel *ch;

	ch = (vcs->channel == VINO_CHANNEL_A) ? &vino->a : &vino->b;

	ch->page_index = 0;
	ch->line_count = 0;

	ch->start_desc_tbl = vino_drvdata->dummy_desc_table.dma;
	ch->next_4_desc = vino_drvdata->dummy_desc_table.dma;

	udelay(VINO_DESC_FETCH_DELAY);
	dprintk("channel %c clear interrupt condition\n",
	       (vcs->channel == VINO_CHANNEL_A) ? 'A':'B');
}