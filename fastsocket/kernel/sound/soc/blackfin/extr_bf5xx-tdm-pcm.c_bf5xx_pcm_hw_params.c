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
struct snd_pcm_substream {int dummy; } ;
struct snd_pcm_hw_params {int dummy; } ;
struct TYPE_2__ {size_t buffer_bytes_max; } ;

/* Variables and functions */
 TYPE_1__ bf5xx_pcm_hardware ; 
 int /*<<< orphan*/  snd_pcm_lib_malloc_pages (struct snd_pcm_substream*,size_t) ; 

__attribute__((used)) static int bf5xx_pcm_hw_params(struct snd_pcm_substream *substream,
	struct snd_pcm_hw_params *params)
{
	size_t size = bf5xx_pcm_hardware.buffer_bytes_max;
	snd_pcm_lib_malloc_pages(substream, size * 4);

	return 0;
}