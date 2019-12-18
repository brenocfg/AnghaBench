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
struct lbs_private {int /*<<< orphan*/  nodename; } ;
struct iw_request_info {int dummy; } ;
struct iw_point {size_t length; int flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  LBS_DEB_WEXT ; 
 int /*<<< orphan*/  lbs_deb_enter (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lbs_deb_leave (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (char*,int /*<<< orphan*/ ,size_t) ; 
 size_t strlen (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int lbs_get_nick(struct net_device *dev, struct iw_request_info *info,
			 struct iw_point *dwrq, char *extra)
{
	struct lbs_private *priv = dev->ml_priv;

	lbs_deb_enter(LBS_DEB_WEXT);

	dwrq->length = strlen(priv->nodename);
	memcpy(extra, priv->nodename, dwrq->length);
	extra[dwrq->length] = '\0';

	dwrq->flags = 1;	/* active */

	lbs_deb_leave(LBS_DEB_WEXT);
	return 0;
}