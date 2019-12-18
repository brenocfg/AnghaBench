#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  zdev_t ;
typedef  int /*<<< orphan*/  wrqu ;
struct TYPE_2__ {int /*<<< orphan*/  length; } ;
union iwreq_data {TYPE_1__ data; } ;
typedef  int /*<<< orphan*/  u16_t ;

/* Variables and functions */
 int /*<<< orphan*/  IWEVCUSTOM ; 
 scalar_t__ ZM_MODE_INFRASTRUCTURE ; 
 int /*<<< orphan*/  memset (union iwreq_data*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  strcpy (char*,char const*) ; 
 int /*<<< orphan*/  strlen (char*) ; 
 int /*<<< orphan*/  wireless_send_event (int /*<<< orphan*/ *,int /*<<< orphan*/ ,union iwreq_data*,char*) ; 
 scalar_t__ zfiWlanQueryWlanMode (int /*<<< orphan*/ *) ; 

void zfLnxMicFailureNotify(zdev_t* dev, u16_t* addr, u16_t status)
{
	static const char *tag = "MLME-MICHAELMICFAILURE.indication";
	union iwreq_data wrqu;
	char buf[128];

	/* TODO: needed parameters: count, type, src address */
	//snprintf(buf, sizeof(buf), "%s(%scast addr=%s)", tag,
	//    (status == ZM_MIC_GROUP_ERROR) ?  "broad" : "uni",
	//    ether_sprintf((u8_t *)addr));

	if (zfiWlanQueryWlanMode(dev) == ZM_MODE_INFRASTRUCTURE)
	{
		strcpy(buf, tag);
	}

	memset(&wrqu, 0, sizeof(wrqu));
	wrqu.data.length = strlen(buf);
	wireless_send_event(dev, IWEVCUSTOM, &wrqu, buf);
}