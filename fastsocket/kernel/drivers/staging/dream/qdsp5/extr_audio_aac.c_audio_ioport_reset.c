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
struct audio {int /*<<< orphan*/  read_lock; int /*<<< orphan*/  read_wait; int /*<<< orphan*/  write_lock; int /*<<< orphan*/  write_wait; } ;

/* Variables and functions */
 int /*<<< orphan*/  audio_flush (struct audio*) ; 
 int /*<<< orphan*/  audio_flush_pcm_buf (struct audio*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wake_up (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void audio_ioport_reset(struct audio *audio)
{
	/* Make sure read/write thread are free from
	 * sleep and knowing that system is not able
	 * to process io request at the moment
	 */
	wake_up(&audio->write_wait);
	mutex_lock(&audio->write_lock);
	audio_flush(audio);
	mutex_unlock(&audio->write_lock);
	wake_up(&audio->read_wait);
	mutex_lock(&audio->read_lock);
	audio_flush_pcm_buf(audio);
	mutex_unlock(&audio->read_lock);
}