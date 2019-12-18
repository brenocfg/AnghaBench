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
struct net_device {struct lbs_private* ml_priv; } ;
struct lbs_private {scalar_t__ mesh_connect_status; } ;
struct iw_request_info {int dummy; } ;
struct iw_point {scalar_t__ length; } ;

/* Variables and functions */
 scalar_t__ LBS_CONNECTED ; 
 int /*<<< orphan*/  LBS_DEB_WEXT ; 
 int /*<<< orphan*/  lbs_deb_enter (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lbs_deb_leave (int /*<<< orphan*/ ) ; 
 scalar_t__ strlen (char*) ; 
 int /*<<< orphan*/  strncpy (char*,char*,int) ; 

__attribute__((used)) static int mesh_get_nick(struct net_device *dev, struct iw_request_info *info,
			 struct iw_point *dwrq, char *extra)
{
	struct lbs_private *priv = dev->ml_priv;

	lbs_deb_enter(LBS_DEB_WEXT);

	/* Use nickname to indicate that mesh is on */

	if (priv->mesh_connect_status == LBS_CONNECTED) {
		strncpy(extra, "Mesh", 12);
		extra[12] = '\0';
		dwrq->length = strlen(extra);
	}

	else {
		extra[0] = '\0';
		dwrq->length = 0;
	}

	lbs_deb_leave(LBS_DEB_WEXT);
	return 0;
}