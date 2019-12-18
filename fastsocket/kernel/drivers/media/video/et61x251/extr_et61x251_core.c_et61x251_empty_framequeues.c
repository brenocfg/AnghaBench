#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  size_t u32 ;
struct et61x251_device {TYPE_2__* frame; int /*<<< orphan*/  outqueue; int /*<<< orphan*/  inqueue; } ;
struct TYPE_3__ {scalar_t__ bytesused; } ;
struct TYPE_4__ {TYPE_1__ buf; int /*<<< orphan*/  state; } ;

/* Variables and functions */
 size_t ET61X251_MAX_FRAMES ; 
 int /*<<< orphan*/  F_UNUSED ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void et61x251_empty_framequeues(struct et61x251_device* cam)
{
	u32 i;

	INIT_LIST_HEAD(&cam->inqueue);
	INIT_LIST_HEAD(&cam->outqueue);

	for (i = 0; i < ET61X251_MAX_FRAMES; i++) {
		cam->frame[i].state = F_UNUSED;
		cam->frame[i].buf.bytesused = 0;
	}
}