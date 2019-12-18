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
struct s3c2410_dma_chan {int /*<<< orphan*/  (* callback_fn ) (struct s3c2410_dma_chan*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ;} ;
struct s3c2410_dma_buf {int /*<<< orphan*/  size; int /*<<< orphan*/  id; } ;
typedef  enum s3c2410_dma_buffresult { ____Placeholder_s3c2410_dma_buffresult } s3c2410_dma_buffresult ;

/* Variables and functions */
 int /*<<< orphan*/  pr_debug (char*,int /*<<< orphan*/  (*) (struct s3c2410_dma_chan*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int),struct s3c2410_dma_buf*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  stub1 (struct s3c2410_dma_chan*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static inline void
s3c2410_dma_buffdone(struct s3c2410_dma_chan *chan, struct s3c2410_dma_buf *buf,
		     enum s3c2410_dma_buffresult result)
{
#if 0
	pr_debug("callback_fn=%p, buf=%p, id=%p, size=%d, result=%d\n",
		 chan->callback_fn, buf, buf->id, buf->size, result);
#endif

	if (chan->callback_fn != NULL) {
		(chan->callback_fn)(chan, buf->id, buf->size, result);
	}
}