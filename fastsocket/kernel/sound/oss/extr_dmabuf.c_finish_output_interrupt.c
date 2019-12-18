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
struct dma_buffparms {int /*<<< orphan*/  callback_parm; int /*<<< orphan*/  (* audio_callback ) (int,int /*<<< orphan*/ ) ;} ;
struct audio_operations {int /*<<< orphan*/  poll_sleeper; int /*<<< orphan*/  out_sleeper; } ;

/* Variables and functions */
 struct audio_operations** audio_devs ; 
 int /*<<< orphan*/  stub1 (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wake_up (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void finish_output_interrupt(int dev, struct dma_buffparms *dmap)
{
	struct audio_operations *adev = audio_devs[dev];

	if (dmap->audio_callback != NULL)
		dmap->audio_callback(dev, dmap->callback_parm);
	wake_up(&adev->out_sleeper);
	wake_up(&adev->poll_sleeper);
}