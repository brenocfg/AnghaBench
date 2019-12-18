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
struct snd_pcm_runtime {struct audiopipe* private_data; } ;
struct TYPE_2__ {scalar_t__ area; } ;
struct audiopipe {TYPE_1__ sgpage; } ;

/* Variables and functions */
 int /*<<< orphan*/  kfree (struct audiopipe*) ; 
 int /*<<< orphan*/  snd_dma_free_pages (TYPE_1__*) ; 

__attribute__((used)) static void audiopipe_free(struct snd_pcm_runtime *runtime)
{
	struct audiopipe *pipe = runtime->private_data;

	if (pipe->sgpage.area)
		snd_dma_free_pages(&pipe->sgpage);
	kfree(pipe);
}