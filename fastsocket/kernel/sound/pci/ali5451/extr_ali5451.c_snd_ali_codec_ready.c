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
struct snd_ali {int dummy; } ;

/* Variables and functions */
 int EIO ; 
 unsigned long jiffies ; 
 unsigned long msecs_to_jiffies (int) ; 
 int /*<<< orphan*/  schedule_timeout_uninterruptible (int) ; 
 unsigned int snd_ali_5451_peek (struct snd_ali*,unsigned int) ; 
 int /*<<< orphan*/  snd_ali_5451_poke (struct snd_ali*,unsigned int,unsigned int) ; 
 int /*<<< orphan*/  snd_printdd (char*) ; 
 int /*<<< orphan*/  time_after_eq (unsigned long,unsigned long) ; 

__attribute__((used)) static int snd_ali_codec_ready(struct snd_ali *codec,
			       unsigned int port)
{
	unsigned long end_time;
	unsigned int res;
	
	end_time = jiffies + msecs_to_jiffies(250);

	for (;;) {
		res = snd_ali_5451_peek(codec,port);
		if (!(res & 0x8000))
			return 0;
		if (!time_after_eq(end_time, jiffies))
			break;
		schedule_timeout_uninterruptible(1);
	}

	snd_ali_5451_poke(codec, port, res & ~0x8000);
	snd_printdd("ali_codec_ready: codec is not ready.\n ");
	return -EIO;
}