#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct sk_buff {unsigned char* data; int len; } ;
struct hfa384x_info_frame {int /*<<< orphan*/  type; int /*<<< orphan*/  len; } ;
struct TYPE_9__ {TYPE_1__* dev; } ;
typedef  TYPE_2__ local_info_t ;
struct TYPE_8__ {int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int /*<<< orphan*/  DEBUG_EXTRA ; 
#define  HFA384X_INFO_COMMTALLIES 131 
#define  HFA384X_INFO_HOSTSCANRESULTS 130 
#define  HFA384X_INFO_LINKSTATUS 129 
#define  HFA384X_INFO_SCANRESULTS 128 
 int /*<<< orphan*/  PDEBUG (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  PDEBUG2 (int /*<<< orphan*/ ,char*,...) ; 
 int le16_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  prism2_info_commtallies (TYPE_2__*,unsigned char*,int) ; 
 int /*<<< orphan*/  prism2_info_hostscanresults (TYPE_2__*,unsigned char*,int) ; 
 int /*<<< orphan*/  prism2_info_linkstatus (TYPE_2__*,unsigned char*,int) ; 
 int /*<<< orphan*/  prism2_info_scanresults (TYPE_2__*,unsigned char*,int) ; 

void hostap_info_process(local_info_t *local, struct sk_buff *skb)
{
	struct hfa384x_info_frame *info;
	unsigned char *buf;
	int left;
#ifndef PRISM2_NO_DEBUG
	int i;
#endif /* PRISM2_NO_DEBUG */

	info = (struct hfa384x_info_frame *) skb->data;
	buf = skb->data + sizeof(*info);
	left = skb->len - sizeof(*info);

	switch (le16_to_cpu(info->type)) {
	case HFA384X_INFO_COMMTALLIES:
		prism2_info_commtallies(local, buf, left);
		break;

#ifndef PRISM2_NO_STATION_MODES
	case HFA384X_INFO_LINKSTATUS:
		prism2_info_linkstatus(local, buf, left);
		break;

	case HFA384X_INFO_SCANRESULTS:
		prism2_info_scanresults(local, buf, left);
		break;

	case HFA384X_INFO_HOSTSCANRESULTS:
		prism2_info_hostscanresults(local, buf, left);
		break;
#endif /* PRISM2_NO_STATION_MODES */

#ifndef PRISM2_NO_DEBUG
	default:
		PDEBUG(DEBUG_EXTRA, "%s: INFO - len=%d type=0x%04x\n",
		       local->dev->name, le16_to_cpu(info->len),
		       le16_to_cpu(info->type));
		PDEBUG(DEBUG_EXTRA, "Unknown info frame:");
		for (i = 0; i < (left < 100 ? left : 100); i++)
			PDEBUG2(DEBUG_EXTRA, " %02x", buf[i]);
		PDEBUG2(DEBUG_EXTRA, "\n");
		break;
#endif /* PRISM2_NO_DEBUG */
	}
}