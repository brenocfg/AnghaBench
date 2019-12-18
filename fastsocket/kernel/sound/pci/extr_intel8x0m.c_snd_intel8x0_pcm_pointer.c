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
struct snd_pcm_substream {int /*<<< orphan*/  runtime; } ;
struct intel8x0m {size_t pcm_pos_shift; } ;
struct ichdev {size_t fragsize1; size_t size; scalar_t__ position; scalar_t__ roff_picb; scalar_t__ reg_offset; } ;
typedef  int /*<<< orphan*/  snd_pcm_uframes_t ;

/* Variables and functions */
 int /*<<< orphan*/  bytes_to_frames (int /*<<< orphan*/ ,size_t) ; 
 struct ichdev* get_ichdev (struct snd_pcm_substream*) ; 
 size_t igetword (struct intel8x0m*,scalar_t__) ; 
 struct intel8x0m* snd_pcm_substream_chip (struct snd_pcm_substream*) ; 

__attribute__((used)) static snd_pcm_uframes_t snd_intel8x0_pcm_pointer(struct snd_pcm_substream *substream)
{
	struct intel8x0m *chip = snd_pcm_substream_chip(substream);
	struct ichdev *ichdev = get_ichdev(substream);
	size_t ptr1, ptr;

	ptr1 = igetword(chip, ichdev->reg_offset + ichdev->roff_picb) << chip->pcm_pos_shift;
	if (ptr1 != 0)
		ptr = ichdev->fragsize1 - ptr1;
	else
		ptr = 0;
	ptr += ichdev->position;
	if (ptr >= ichdev->size)
		return 0;
	return bytes_to_frames(substream->runtime, ptr);
}