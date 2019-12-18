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
struct net_device {int dummy; } ;
struct iw_request_info {int dummy; } ;
struct iw_point {int flags; int length; } ;
struct atmel_private {int default_key; int* wep_key_len; int /*<<< orphan*/ * wep_keys; scalar_t__ exclude_unencrypted; int /*<<< orphan*/  wep_is_on; } ;

/* Variables and functions */
 int IW_ENCODE_DISABLED ; 
 int IW_ENCODE_INDEX ; 
 int IW_ENCODE_OPEN ; 
 int IW_ENCODE_RESTRICTED ; 
 int /*<<< orphan*/  memcpy (char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  memset (char*,int /*<<< orphan*/ ,int) ; 
 struct atmel_private* netdev_priv (struct net_device*) ; 

__attribute__((used)) static int atmel_get_encode(struct net_device *dev,
			    struct iw_request_info *info,
			    struct iw_point *dwrq,
			    char *extra)
{
	struct atmel_private *priv = netdev_priv(dev);
	int index = (dwrq->flags & IW_ENCODE_INDEX) - 1;

	if (!priv->wep_is_on)
		dwrq->flags = IW_ENCODE_DISABLED;
	else {
		if (priv->exclude_unencrypted)
			dwrq->flags = IW_ENCODE_RESTRICTED;
		else
			dwrq->flags = IW_ENCODE_OPEN;
	}
		/* Which key do we want ? -1 -> tx index */
	if (index < 0 || index >= 4)
		index = priv->default_key;
	dwrq->flags |= index + 1;
	/* Copy the key to the user buffer */
	dwrq->length = priv->wep_key_len[index];
	if (dwrq->length > 16) {
		dwrq->length = 0;
	} else {
		memset(extra, 0, 16);
		memcpy(extra, priv->wep_keys[index], dwrq->length);
	}

	return 0;
}