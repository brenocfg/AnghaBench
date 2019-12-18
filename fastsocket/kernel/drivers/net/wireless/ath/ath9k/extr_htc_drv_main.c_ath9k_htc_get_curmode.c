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
struct ath9k_htc_priv {int dummy; } ;
struct ath9k_channel {int chanmode; } ;
typedef  enum htc_phymode { ____Placeholder_htc_phymode } htc_phymode ;

/* Variables and functions */
#define  CHANNEL_A 135 
#define  CHANNEL_A_HT20 134 
#define  CHANNEL_A_HT40MINUS 133 
#define  CHANNEL_A_HT40PLUS 132 
#define  CHANNEL_G 131 
#define  CHANNEL_G_HT20 130 
#define  CHANNEL_G_HT40MINUS 129 
#define  CHANNEL_G_HT40PLUS 128 
 int EINVAL ; 
 int HTC_MODE_11NA ; 
 int HTC_MODE_11NG ; 
 int /*<<< orphan*/  WARN_ON (int) ; 

__attribute__((used)) static enum htc_phymode ath9k_htc_get_curmode(struct ath9k_htc_priv *priv,
					      struct ath9k_channel *ichan)
{
	enum htc_phymode mode;

	mode = -EINVAL;

	switch (ichan->chanmode) {
	case CHANNEL_G:
	case CHANNEL_G_HT20:
	case CHANNEL_G_HT40PLUS:
	case CHANNEL_G_HT40MINUS:
		mode = HTC_MODE_11NG;
		break;
	case CHANNEL_A:
	case CHANNEL_A_HT20:
	case CHANNEL_A_HT40PLUS:
	case CHANNEL_A_HT40MINUS:
		mode = HTC_MODE_11NA;
		break;
	default:
		break;
	}

	WARN_ON(mode < 0);

	return mode;
}