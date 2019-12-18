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
struct snd_pcm_runtime {int channels; int /*<<< orphan*/  format; } ;

/* Variables and functions */
 int ALS4000_FORMAT_16BIT ; 
 int ALS4000_FORMAT_SIGNED ; 
 int ALS4000_FORMAT_STEREO ; 
 int snd_pcm_format_physical_width (int /*<<< orphan*/ ) ; 
 scalar_t__ snd_pcm_format_signed (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int snd_als4000_get_format(struct snd_pcm_runtime *runtime)
{
	int result;

	result = 0;
	if (snd_pcm_format_signed(runtime->format))
		result |= ALS4000_FORMAT_SIGNED;
	if (snd_pcm_format_physical_width(runtime->format) == 16)
		result |= ALS4000_FORMAT_16BIT;
	if (runtime->channels > 1)
		result |= ALS4000_FORMAT_STEREO;
	return result;
}