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
struct ar9170 {int /*<<< orphan*/ * noise; } ;
typedef  int ssize_t ;

/* Variables and functions */
 int /*<<< orphan*/  ADD (char*,int,size_t,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int carl9170_get_noisefloor (struct ar9170*) ; 

__attribute__((used)) static char *carl9170_debugfs_phy_noise_read(struct ar9170 *ar, char *buf,
					     size_t bufsize, ssize_t *len)
{
	int err;

	err = carl9170_get_noisefloor(ar);
	if (err) {
		*len = err;
		return buf;
	}

	ADD(buf, *len, bufsize, "Chain 0: %10d dBm, ext. chan.:%10d dBm\n",
	    ar->noise[0], ar->noise[2]);
	ADD(buf, *len, bufsize, "Chain 2: %10d dBm, ext. chan.:%10d dBm\n",
	    ar->noise[1], ar->noise[3]);

	return buf;
}