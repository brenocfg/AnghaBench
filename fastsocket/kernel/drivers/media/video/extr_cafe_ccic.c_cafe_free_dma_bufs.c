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
struct cafe_camera {int nbufs; int /*<<< orphan*/ ** dma_bufs; int /*<<< orphan*/ * dma_handles; int /*<<< orphan*/  dma_buf_size; TYPE_1__* pdev; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  dma_free_coherent (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void cafe_free_dma_bufs(struct cafe_camera *cam)
{
	int i;

	for (i = 0; i < cam->nbufs; i++) {
		dma_free_coherent(&cam->pdev->dev, cam->dma_buf_size,
				cam->dma_bufs[i], cam->dma_handles[i]);
		cam->dma_bufs[i] = NULL;
	}
	cam->nbufs = 0;
}