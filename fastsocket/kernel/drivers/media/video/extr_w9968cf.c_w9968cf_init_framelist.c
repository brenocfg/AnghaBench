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
typedef  size_t u8 ;
struct w9968cf_device {size_t nbuffers; TYPE_1__* frame; int /*<<< orphan*/ ** requested_frame; } ;
struct TYPE_2__ {int /*<<< orphan*/  status; scalar_t__ queued; } ;

/* Variables and functions */
 int /*<<< orphan*/  F_UNUSED ; 

__attribute__((used)) static void w9968cf_init_framelist(struct w9968cf_device* cam)
{
	u8 i;

	for (i = 0; i < cam->nbuffers; i++) {
		cam->requested_frame[i] = NULL;
		cam->frame[i].queued = 0;
		cam->frame[i].status = F_UNUSED;
	}
}