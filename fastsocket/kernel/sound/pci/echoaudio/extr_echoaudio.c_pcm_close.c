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
struct echoaudio {int can_set_rate; scalar_t__ rate_set; int /*<<< orphan*/  opencount; } ;

/* Variables and functions */
 int /*<<< orphan*/  DE_ACT (char*) ; 
 int /*<<< orphan*/  atomic_dec (int /*<<< orphan*/ *) ; 
 int atomic_read (int /*<<< orphan*/ *) ; 
 struct echoaudio* snd_pcm_substream_chip (struct snd_pcm_substream*) ; 

__attribute__((used)) static int pcm_close(struct snd_pcm_substream *substream)
{
	struct echoaudio *chip = snd_pcm_substream_chip(substream);
	int oc;

	/* Nothing to do here. Audio is already off and pipe will be
	 * freed by its callback
	 */
	DE_ACT(("pcm_close\n"));

	atomic_dec(&chip->opencount);
	oc = atomic_read(&chip->opencount);
	DE_ACT(("pcm_close  oc=%d  cs=%d  rs=%d\n", oc,
		chip->can_set_rate, chip->rate_set));
	if (oc < 2)
		chip->can_set_rate = 1;
	if (oc == 0)
		chip->rate_set = 0;
	DE_ACT(("pcm_close2 oc=%d  cs=%d  rs=%d\n", oc,
		chip->can_set_rate,chip->rate_set));

	return 0;
}