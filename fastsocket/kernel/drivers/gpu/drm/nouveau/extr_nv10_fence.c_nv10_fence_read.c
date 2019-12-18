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
typedef  int /*<<< orphan*/  u32 ;
struct nouveau_channel {int /*<<< orphan*/  object; } ;

/* Variables and functions */
 int /*<<< orphan*/  nv_ro32 (int /*<<< orphan*/ ,int) ; 

u32
nv10_fence_read(struct nouveau_channel *chan)
{
	return nv_ro32(chan->object, 0x0048);
}