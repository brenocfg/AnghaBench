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
struct snd_pcm_substream {struct snd_pcm_runtime* runtime; } ;
struct snd_pcm_runtime {TYPE_1__* control; scalar_t__ boundary; scalar_t__ buffer_size; } ;
typedef  scalar_t__ snd_pcm_uframes_t ;
struct TYPE_2__ {scalar_t__ appl_ptr; } ;

/* Variables and functions */

__attribute__((used)) static void snd_pcm_oss_simulate_fill(struct snd_pcm_substream *substream,
				      snd_pcm_uframes_t hw_ptr)
{
	struct snd_pcm_runtime *runtime = substream->runtime;
	snd_pcm_uframes_t appl_ptr;
	appl_ptr = hw_ptr + runtime->buffer_size;
	appl_ptr %= runtime->boundary;
	runtime->control->appl_ptr = appl_ptr;
}