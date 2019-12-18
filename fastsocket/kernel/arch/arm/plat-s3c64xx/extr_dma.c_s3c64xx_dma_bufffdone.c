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
struct s3c64xx_dma_buff {int /*<<< orphan*/  pw; } ;
struct s3c2410_dma_chan {int /*<<< orphan*/  (* callback_fn ) (struct s3c2410_dma_chan*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ;} ;
typedef  enum s3c2410_dma_buffresult { ____Placeholder_s3c2410_dma_buffresult } s3c2410_dma_buffresult ;

/* Variables and functions */
 int /*<<< orphan*/  stub1 (struct s3c2410_dma_chan*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static inline void s3c64xx_dma_bufffdone(struct s3c2410_dma_chan *chan,
					 struct s3c64xx_dma_buff *buf,
					 enum s3c2410_dma_buffresult result)
{
	if (chan->callback_fn != NULL)
		(chan->callback_fn)(chan, buf->pw, 0, result);
}