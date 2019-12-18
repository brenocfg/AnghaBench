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
struct snd_pcm_substream {struct snd_pcm_runtime* runtime; } ;
struct snd_pcm_runtime {int dummy; } ;
struct TYPE_3__ {long buffer_bytes; } ;
struct TYPE_4__ {TYPE_1__ oss; } ;

/* Variables and functions */
 long bytes_to_frames (struct snd_pcm_runtime*,long) ; 
 TYPE_2__* oss_runtime (struct snd_pcm_runtime*) ; 
 long snd_pcm_lib_buffer_bytes (struct snd_pcm_substream*) ; 

__attribute__((used)) static long snd_pcm_alsa_frames(struct snd_pcm_substream *substream, long bytes)
{
	struct snd_pcm_runtime *runtime = substream->runtime;
	long buffer_size = snd_pcm_lib_buffer_bytes(substream);
	if (buffer_size == oss_runtime(runtime)->oss.buffer_bytes)
		return bytes_to_frames(runtime, bytes);
	return bytes_to_frames(runtime, (buffer_size * bytes) / oss_runtime(runtime)->oss.buffer_bytes);
}