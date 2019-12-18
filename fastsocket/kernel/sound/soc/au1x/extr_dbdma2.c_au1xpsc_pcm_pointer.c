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
struct snd_pcm_substream {int /*<<< orphan*/  runtime; } ;
typedef  int /*<<< orphan*/  snd_pcm_uframes_t ;
struct TYPE_2__ {int /*<<< orphan*/  pos; } ;

/* Variables and functions */
 size_t SUBSTREAM_TYPE (struct snd_pcm_substream*) ; 
 TYPE_1__** au1xpsc_audio_pcmdma ; 
 int /*<<< orphan*/  bytes_to_frames (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static snd_pcm_uframes_t
au1xpsc_pcm_pointer(struct snd_pcm_substream *substream)
{
	return bytes_to_frames(substream->runtime,
		au1xpsc_audio_pcmdma[SUBSTREAM_TYPE(substream)]->pos);
}