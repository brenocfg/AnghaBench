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
struct dma_buf {TYPE_1__* ops; } ;
typedef  enum dma_data_direction { ____Placeholder_dma_data_direction } dma_data_direction ;
struct TYPE_2__ {int /*<<< orphan*/  (* end_cpu_access ) (struct dma_buf*,size_t,size_t,int) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  WARN_ON (int) ; 
 int /*<<< orphan*/  stub1 (struct dma_buf*,size_t,size_t,int) ; 

void dma_buf_end_cpu_access(struct dma_buf *dmabuf, size_t start, size_t len,
			    enum dma_data_direction direction)
{
	WARN_ON(!dmabuf);

	if (dmabuf->ops->end_cpu_access)
		dmabuf->ops->end_cpu_access(dmabuf, start, len, direction);
}