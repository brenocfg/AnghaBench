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
struct qeth_card {int state; int /*<<< orphan*/  lan_online; } ;
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
typedef  int /*<<< orphan*/  ssize_t ;

/* Variables and functions */
#define  CARD_STATE_DOWN 132 
#define  CARD_STATE_HARDSETUP 131 
#define  CARD_STATE_RECOVER 130 
#define  CARD_STATE_SOFTSETUP 129 
#define  CARD_STATE_UP 128 
 int /*<<< orphan*/  EINVAL ; 
 struct qeth_card* dev_get_drvdata (struct device*) ; 
 int /*<<< orphan*/  sprintf (char*,char*) ; 

__attribute__((used)) static ssize_t qeth_dev_state_show(struct device *dev,
				struct device_attribute *attr, char *buf)
{
	struct qeth_card *card = dev_get_drvdata(dev);
	if (!card)
		return -EINVAL;

	switch (card->state) {
	case CARD_STATE_DOWN:
		return sprintf(buf, "DOWN\n");
	case CARD_STATE_HARDSETUP:
		return sprintf(buf, "HARDSETUP\n");
	case CARD_STATE_SOFTSETUP:
		return sprintf(buf, "SOFTSETUP\n");
	case CARD_STATE_UP:
		if (card->lan_online)
		return sprintf(buf, "UP (LAN ONLINE)\n");
		else
			return sprintf(buf, "UP (LAN OFFLINE)\n");
	case CARD_STATE_RECOVER:
		return sprintf(buf, "RECOVER\n");
	default:
		return sprintf(buf, "UNKNOWN\n");
	}
}