#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct net_device {int dummy; } ;
struct TYPE_3__ {int /*<<< orphan*/  raw; } ;
struct TYPE_4__ {TYPE_1__ dgid; } ;
struct ipoib_path {int query_id; int /*<<< orphan*/  done; int /*<<< orphan*/ * query; TYPE_2__ pathrec; } ;
struct ipoib_dev_priv {int /*<<< orphan*/  port; int /*<<< orphan*/  ca; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_ATOMIC ; 
 int IB_SA_PATH_REC_DGID ; 
 int IB_SA_PATH_REC_NUMB_PATH ; 
 int IB_SA_PATH_REC_PKEY ; 
 int IB_SA_PATH_REC_SGID ; 
 int IB_SA_PATH_REC_TRAFFIC_CLASS ; 
 int /*<<< orphan*/  complete (int /*<<< orphan*/ *) ; 
 int ib_sa_path_rec_get (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_2__*,int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct ipoib_path*,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  init_completion (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ipoib_dbg (struct ipoib_dev_priv*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ipoib_sa_client ; 
 int /*<<< orphan*/  ipoib_warn (struct ipoib_dev_priv*,char*,int) ; 
 struct ipoib_dev_priv* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  path_rec_completion ; 

__attribute__((used)) static int path_rec_start(struct net_device *dev,
			  struct ipoib_path *path)
{
	struct ipoib_dev_priv *priv = netdev_priv(dev);

	ipoib_dbg(priv, "Start path record lookup for %pI6\n",
		  path->pathrec.dgid.raw);

	init_completion(&path->done);

	path->query_id =
		ib_sa_path_rec_get(&ipoib_sa_client, priv->ca, priv->port,
				   &path->pathrec,
				   IB_SA_PATH_REC_DGID		|
				   IB_SA_PATH_REC_SGID		|
				   IB_SA_PATH_REC_NUMB_PATH	|
				   IB_SA_PATH_REC_TRAFFIC_CLASS |
				   IB_SA_PATH_REC_PKEY,
				   1000, GFP_ATOMIC,
				   path_rec_completion,
				   path, &path->query);
	if (path->query_id < 0) {
		ipoib_warn(priv, "ib_sa_path_rec_get failed: %d\n", path->query_id);
		path->query = NULL;
		complete(&path->done);
		return path->query_id;
	}

	return 0;
}