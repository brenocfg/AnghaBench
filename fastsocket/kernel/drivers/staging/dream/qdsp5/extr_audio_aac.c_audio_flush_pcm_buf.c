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
typedef  size_t uint8_t ;
struct audio {scalar_t__ fill_next; scalar_t__ read_next; scalar_t__ buf_refresh; TYPE_1__* in; } ;
struct TYPE_2__ {scalar_t__ used; } ;

/* Variables and functions */
 size_t PCM_BUF_MAX_COUNT ; 

__attribute__((used)) static void audio_flush_pcm_buf(struct audio *audio)
{
	uint8_t index;

	for (index = 0; index < PCM_BUF_MAX_COUNT; index++)
		audio->in[index].used = 0;
	audio->buf_refresh = 0;
	audio->read_next = 0;
	audio->fill_next = 0;
}