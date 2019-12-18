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
struct sport_device {unsigned int tx_curr_frag; unsigned int tx_fragsize; } ;

/* Variables and functions */
 unsigned int sport_curr_offset_tx (struct sport_device*) ; 

__attribute__((used)) static unsigned int sport_tx_curr_frag(struct sport_device *sport)
{
	return sport->tx_curr_frag = sport_curr_offset_tx(sport) /
			sport->tx_fragsize;
}