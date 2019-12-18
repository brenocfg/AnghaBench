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
struct s3c64xx_dma_buff {int /*<<< orphan*/  lli; int /*<<< orphan*/  lli_dma; struct s3c64xx_dma_buff* next; } ;
struct s3c2410_dma_chan {int /*<<< orphan*/  number; struct s3c64xx_dma_buff* end; struct s3c64xx_dma_buff* next; int /*<<< orphan*/  curr; } ;

/* Variables and functions */
 scalar_t__ debug_show_buffs ; 
 int /*<<< orphan*/  pr_debug (char*,int /*<<< orphan*/ ,struct s3c64xx_dma_buff*,...) ; 
 int /*<<< orphan*/  show_lli (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void dbg_showbuffs(struct s3c2410_dma_chan *chan)
{
	struct s3c64xx_dma_buff *ptr;
	struct s3c64xx_dma_buff *end;

	pr_debug("DMA%d: buffs next %p, curr %p, end %p\n",
		 chan->number, chan->next, chan->curr, chan->end);

	ptr = chan->next;
	end = chan->end;

	if (debug_show_buffs) {
		for (; ptr != NULL; ptr = ptr->next) {
			pr_debug("DMA%d: %08x ",
				 chan->number, ptr->lli_dma);
			show_lli(ptr->lli);
		}
	}
}