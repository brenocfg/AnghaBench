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
struct snd_pcm_runtime {int /*<<< orphan*/  hw_ptr_interrupt; } ;
typedef  int /*<<< orphan*/  snd_pcm_uframes_t ;

/* Variables and functions */

__attribute__((used)) static inline
snd_pcm_uframes_t get_hw_ptr_period(struct snd_pcm_runtime *runtime)
{
	return runtime->hw_ptr_interrupt;
}