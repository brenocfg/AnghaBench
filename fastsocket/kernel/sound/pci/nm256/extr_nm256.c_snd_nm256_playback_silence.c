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
struct snd_pcm_substream {struct snd_pcm_runtime* runtime; } ;
struct snd_pcm_runtime {struct nm256_stream* private_data; } ;
struct nm256_stream {scalar_t__ bufptr; } ;
typedef  scalar_t__ snd_pcm_uframes_t ;

/* Variables and functions */
 scalar_t__ frames_to_bytes (struct snd_pcm_runtime*,scalar_t__) ; 
 int /*<<< orphan*/  memset_io (scalar_t__,int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static int
snd_nm256_playback_silence(struct snd_pcm_substream *substream,
			   int channel, /* not used (interleaved data) */
			   snd_pcm_uframes_t pos,
			   snd_pcm_uframes_t count)
{
	struct snd_pcm_runtime *runtime = substream->runtime;
	struct nm256_stream *s = runtime->private_data;
	count = frames_to_bytes(runtime, count);
	pos = frames_to_bytes(runtime, pos);
	memset_io(s->bufptr + pos, 0, count);
	return 0;
}