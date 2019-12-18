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
struct snd_pcm_substream {int dummy; } ;
struct rme32 {int /*<<< orphan*/  playback_pcm; } ;
typedef  int /*<<< orphan*/  snd_pcm_uframes_t ;

/* Variables and functions */
 int /*<<< orphan*/  snd_pcm_indirect_playback_pointer (struct snd_pcm_substream*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 struct rme32* snd_pcm_substream_chip (struct snd_pcm_substream*) ; 
 int /*<<< orphan*/  snd_rme32_pcm_byteptr (struct rme32*) ; 

__attribute__((used)) static snd_pcm_uframes_t
snd_rme32_playback_fd_pointer(struct snd_pcm_substream *substream)
{
	struct rme32 *rme32 = snd_pcm_substream_chip(substream);
	return snd_pcm_indirect_playback_pointer(substream, &rme32->playback_pcm,
						 snd_rme32_pcm_byteptr(rme32));
}