#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct virtnet_info {scalar_t__ pages; TYPE_2__* vdev; } ;
struct TYPE_5__ {TYPE_1__* config; } ;
struct TYPE_4__ {int /*<<< orphan*/  (* del_vqs ) (TYPE_2__*) ;int /*<<< orphan*/  (* reset ) (TYPE_2__*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  __free_pages (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free_unused_bufs (struct virtnet_info*) ; 
 int /*<<< orphan*/  get_a_page (struct virtnet_info*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (TYPE_2__*) ; 
 int /*<<< orphan*/  stub2 (TYPE_2__*) ; 

__attribute__((used)) static void remove_vq_common(struct virtnet_info *vi)
{
	vi->vdev->config->reset(vi->vdev);

	/* Free unused buffers in both send and recv, if any. */
	free_unused_bufs(vi);

	vi->vdev->config->del_vqs(vi->vdev);

	while (vi->pages)
		__free_pages(get_a_page(vi, GFP_KERNEL), 0);
}