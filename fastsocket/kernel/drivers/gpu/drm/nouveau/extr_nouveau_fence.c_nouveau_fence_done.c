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
struct nouveau_fence {scalar_t__ channel; } ;

/* Variables and functions */
 int /*<<< orphan*/  nouveau_fence_update (scalar_t__) ; 

bool
nouveau_fence_done(struct nouveau_fence *fence)
{
	if (fence->channel)
		nouveau_fence_update(fence->channel);
	return !fence->channel;
}