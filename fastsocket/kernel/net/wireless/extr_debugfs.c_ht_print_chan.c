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
struct ieee80211_channel {int flags; int center_freq; } ;

/* Variables and functions */
 int IEEE80211_CHAN_DISABLED ; 
 int IEEE80211_CHAN_NO_HT40MINUS ; 
 int IEEE80211_CHAN_NO_HT40PLUS ; 
 scalar_t__ WARN_ON (int) ; 
 int snprintf (char*,int,char*,int,...) ; 

__attribute__((used)) static int ht_print_chan(struct ieee80211_channel *chan,
			 char *buf, int buf_size, int offset)
{
	if (WARN_ON(offset > buf_size))
		return 0;

	if (chan->flags & IEEE80211_CHAN_DISABLED)
		return snprintf(buf + offset,
				buf_size - offset,
				"%d Disabled\n",
				chan->center_freq);

	return snprintf(buf + offset,
			buf_size - offset,
			"%d HT40 %c%c\n",
			chan->center_freq,
			(chan->flags & IEEE80211_CHAN_NO_HT40MINUS) ? ' ' : '-',
			(chan->flags & IEEE80211_CHAN_NO_HT40PLUS)  ? ' ' : '+');
}