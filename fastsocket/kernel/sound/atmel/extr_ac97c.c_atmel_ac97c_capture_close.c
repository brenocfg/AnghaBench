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
struct atmel_ac97c {int /*<<< orphan*/ * capture_substream; scalar_t__ cur_format; scalar_t__ cur_rate; int /*<<< orphan*/  opened; } ;

/* Variables and functions */
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  opened_mutex ; 
 struct atmel_ac97c* snd_pcm_substream_chip (struct snd_pcm_substream*) ; 

__attribute__((used)) static int atmel_ac97c_capture_close(struct snd_pcm_substream *substream)
{
	struct atmel_ac97c *chip = snd_pcm_substream_chip(substream);

	mutex_lock(&opened_mutex);
	chip->opened--;
	if (!chip->opened) {
		chip->cur_rate = 0;
		chip->cur_format = 0;
	}
	mutex_unlock(&opened_mutex);

	chip->capture_substream = NULL;

	return 0;
}