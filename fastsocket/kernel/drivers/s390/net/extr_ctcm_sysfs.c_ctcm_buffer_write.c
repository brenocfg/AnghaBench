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
struct net_device {int flags; int mtu; } ;
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
struct ctcm_priv {int buffer_size; TYPE_1__** channel; } ;
typedef  size_t ssize_t ;
struct TYPE_2__ {int max_bufsize; int /*<<< orphan*/  flags; struct net_device* netdev; } ;

/* Variables and functions */
 int /*<<< orphan*/  CHANNEL_FLAGS_BUFSIZE_CHANGED ; 
 int CTCM_BUFSIZE_LIMIT ; 
 int /*<<< orphan*/  CTCM_DBF_DEV (int /*<<< orphan*/ ,struct net_device*,char const*) ; 
 int /*<<< orphan*/  CTCM_DBF_TEXT (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  CTC_DBF_ERROR ; 
 size_t EINVAL ; 
 size_t ENODEV ; 
 int IFF_RUNNING ; 
 int LL_HEADER_LENGTH ; 
 size_t READ ; 
 int /*<<< orphan*/  SETUP ; 
 size_t WRITE ; 
 struct ctcm_priv* dev_get_drvdata (struct device*) ; 
 int /*<<< orphan*/  sscanf (char const*,char*,int*) ; 

__attribute__((used)) static ssize_t ctcm_buffer_write(struct device *dev,
		struct device_attribute *attr, const char *buf, size_t count)
{
	struct net_device *ndev;
	int bs1;
	struct ctcm_priv *priv = dev_get_drvdata(dev);

	if (!(priv && priv->channel[READ] &&
			(ndev = priv->channel[READ]->netdev))) {
		CTCM_DBF_TEXT(SETUP, CTC_DBF_ERROR, "bfnondev");
		return -ENODEV;
	}

	sscanf(buf, "%u", &bs1);
	if (bs1 > CTCM_BUFSIZE_LIMIT)
					goto einval;
	if (bs1 < (576 + LL_HEADER_LENGTH + 2))
					goto einval;
	priv->buffer_size = bs1;	/* just to overwrite the default */

	if ((ndev->flags & IFF_RUNNING) &&
	    (bs1 < (ndev->mtu + LL_HEADER_LENGTH + 2)))
					goto einval;

	priv->channel[READ]->max_bufsize = bs1;
	priv->channel[WRITE]->max_bufsize = bs1;
	if (!(ndev->flags & IFF_RUNNING))
		ndev->mtu = bs1 - LL_HEADER_LENGTH - 2;
	priv->channel[READ]->flags |= CHANNEL_FLAGS_BUFSIZE_CHANGED;
	priv->channel[WRITE]->flags |= CHANNEL_FLAGS_BUFSIZE_CHANGED;

	CTCM_DBF_DEV(SETUP, ndev, buf);
	return count;

einval:
	CTCM_DBF_DEV(SETUP, ndev, "buff_err");
	return -EINVAL;
}