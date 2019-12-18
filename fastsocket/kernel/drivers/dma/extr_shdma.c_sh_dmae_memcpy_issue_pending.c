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
struct sh_dmae_chan {int dummy; } ;
struct dma_chan {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  sh_chan_xfer_ld_queue (struct sh_dmae_chan*) ; 
 struct sh_dmae_chan* to_sh_chan (struct dma_chan*) ; 

__attribute__((used)) static void sh_dmae_memcpy_issue_pending(struct dma_chan *chan)
{
	struct sh_dmae_chan *sh_chan = to_sh_chan(chan);
	sh_chan_xfer_ld_queue(sh_chan);
}