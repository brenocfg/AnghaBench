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
struct ath_hw {int dummy; } ;
struct ath9k_channel {int chanmode; int channel; } ;

/* Variables and functions */
#define  CHANNEL_A 136 
#define  CHANNEL_A_HT20 135 
#define  CHANNEL_A_HT40MINUS 134 
#define  CHANNEL_A_HT40PLUS 133 
#define  CHANNEL_B 132 
#define  CHANNEL_G 131 
#define  CHANNEL_G_HT20 130 
#define  CHANNEL_G_HT40MINUS 129 
#define  CHANNEL_G_HT40PLUS 128 
 int EINVAL ; 

__attribute__((used)) static int ar9550_hw_get_modes_txgain_index(struct ath_hw *ah,
					    struct ath9k_channel *chan)
{
	int ret;

	switch (chan->chanmode) {
	case CHANNEL_A:
	case CHANNEL_A_HT20:
		if (chan->channel <= 5350)
			ret = 1;
		else if ((chan->channel > 5350) && (chan->channel <= 5600))
			ret = 3;
		else
			ret = 5;
		break;

	case CHANNEL_A_HT40PLUS:
	case CHANNEL_A_HT40MINUS:
		if (chan->channel <= 5350)
			ret = 2;
		else if ((chan->channel > 5350) && (chan->channel <= 5600))
			ret = 4;
		else
			ret = 6;
		break;

	case CHANNEL_G:
	case CHANNEL_G_HT20:
	case CHANNEL_B:
		ret = 8;
		break;

	case CHANNEL_G_HT40PLUS:
	case CHANNEL_G_HT40MINUS:
		ret = 7;
		break;

	default:
		ret = -EINVAL;
	}

	return ret;
}