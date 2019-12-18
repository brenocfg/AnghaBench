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
struct dumchannel {int channelnr; scalar_t__ dum_ch_ctrl; scalar_t__ dum_ch_conf; scalar_t__ dum_ch_max; scalar_t__ dum_ch_min; } ;

/* Variables and functions */
 int /*<<< orphan*/  put_channel (struct dumchannel) ; 

__attribute__((used)) static void clear_channel(int channr)
{
	struct dumchannel chan;

	chan.channelnr = channr;
	chan.dum_ch_min = 0;
	chan.dum_ch_max = 0;
	chan.dum_ch_conf = 0;
	chan.dum_ch_ctrl = 0;

	put_channel(chan);
}