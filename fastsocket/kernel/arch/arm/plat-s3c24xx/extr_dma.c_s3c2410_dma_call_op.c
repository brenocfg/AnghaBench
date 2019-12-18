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
struct s3c2410_dma_chan {int /*<<< orphan*/  (* op_fn ) (struct s3c2410_dma_chan*,int) ;} ;
typedef  enum s3c2410_chan_op { ____Placeholder_s3c2410_chan_op } s3c2410_chan_op ;

/* Variables and functions */
 int /*<<< orphan*/  stub1 (struct s3c2410_dma_chan*,int) ; 

__attribute__((used)) static void
s3c2410_dma_call_op(struct s3c2410_dma_chan *chan, enum s3c2410_chan_op op)
{
	if (chan->op_fn != NULL) {
		(chan->op_fn)(chan, op);
	}
}