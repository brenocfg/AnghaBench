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
struct TYPE_2__ {int /*<<< orphan*/  fm_dev; } ;
struct poseidon {TYPE_1__ radio_data; } ;

/* Variables and functions */
 int /*<<< orphan*/  destroy_video_device (int /*<<< orphan*/ *) ; 

int poseidon_fm_exit(struct poseidon *p)
{
	destroy_video_device(&p->radio_data.fm_dev);
	return 0;
}