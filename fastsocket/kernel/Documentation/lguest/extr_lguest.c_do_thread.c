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
struct virtqueue {int /*<<< orphan*/  (* service ) (struct virtqueue*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  stub1 (struct virtqueue*) ; 

__attribute__((used)) static int do_thread(void *_vq)
{
	struct virtqueue *vq = _vq;

	for (;;)
		vq->service(vq);
	return 0;
}