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
struct es1968 {int bobclient; int bob_freq; } ;

/* Variables and functions */
 int /*<<< orphan*/  snd_es1968_bob_start (struct es1968*) ; 
 int /*<<< orphan*/  snd_es1968_bob_stop (struct es1968*) ; 

__attribute__((used)) static void snd_es1968_bob_inc(struct es1968 *chip, int freq)
{
	chip->bobclient++;
	if (chip->bobclient == 1) {
		chip->bob_freq = freq;
		snd_es1968_bob_start(chip);
	} else if (chip->bob_freq < freq) {
		snd_es1968_bob_stop(chip);
		chip->bob_freq = freq;
		snd_es1968_bob_start(chip);
	}
}