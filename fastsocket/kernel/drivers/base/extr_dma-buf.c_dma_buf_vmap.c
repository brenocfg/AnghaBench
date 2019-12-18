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
struct TYPE_2__ {void* (* vmap ) (struct dma_buf*) ;} ;

/* Variables and functions */
 scalar_t__ WARN_ON (int) ; 
 void* stub1 (struct dma_buf*) ; 

void *dma_buf_vmap(struct dma_buf *dmabuf)
{
	if (WARN_ON(!dmabuf))
		return NULL;

	if (dmabuf->ops->vmap)
		return dmabuf->ops->vmap(dmabuf);
	return NULL;
}