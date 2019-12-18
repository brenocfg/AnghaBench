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
struct sport_device {int tx_fragsize; scalar_t__ tx_buf; } ;
struct snd_ac97 {int dummy; } ;
struct ac97_frame {int ac97_addr; int ac97_data; int /*<<< orphan*/  ac97_tag; } ;
typedef  int __u16 ;

/* Variables and functions */
 int /*<<< orphan*/  TAG_CMD ; 
 size_t* cmd_count ; 
 int /*<<< orphan*/  pr_debug (char*,int,int,...) ; 
 struct sport_device* sport_handle ; 
 int /*<<< orphan*/  sport_incfrag (struct sport_device*,int*,int) ; 
 int sport_tx_curr_frag (struct sport_device*) ; 

__attribute__((used)) static void enqueue_cmd(struct snd_ac97 *ac97, __u16 addr, __u16 data)
{
	struct sport_device *sport = sport_handle;
	int nextfrag = sport_tx_curr_frag(sport);
	struct ac97_frame *nextwrite;

	sport_incfrag(sport, &nextfrag, 1);

	nextwrite = (struct ac97_frame *)(sport->tx_buf +
			nextfrag * sport->tx_fragsize);
	pr_debug("sport->tx_buf:%p, nextfrag:0x%x nextwrite:%p, cmd_count:%d\n",
		sport->tx_buf, nextfrag, nextwrite, cmd_count[nextfrag]);
	nextwrite[cmd_count[nextfrag]].ac97_tag |= TAG_CMD;
	nextwrite[cmd_count[nextfrag]].ac97_addr = addr;
	nextwrite[cmd_count[nextfrag]].ac97_data = data;
	++cmd_count[nextfrag];
	pr_debug("ac97_sport: Inserting %02x/%04x into fragment %d\n",
			addr >> 8, data, nextfrag);
}