#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_5__ ;
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct net_device {scalar_t__ type; TYPE_4__* ml_priv; } ;
struct TYPE_8__ {int /*<<< orphan*/  fr_pvc_info; } ;
struct TYPE_9__ {scalar_t__ type; int size; TYPE_2__ ifs_ifsu; } ;
struct ifreq {TYPE_3__ ifr_settings; } ;
struct TYPE_10__ {TYPE_1__* frad; int /*<<< orphan*/  dlci; } ;
typedef  TYPE_4__ pvc_device ;
typedef  int /*<<< orphan*/  info ;
struct TYPE_11__ {int /*<<< orphan*/  master; int /*<<< orphan*/  dlci; } ;
typedef  TYPE_5__ fr_proto_pvc_info ;
struct TYPE_7__ {int /*<<< orphan*/  name; } ;

/* Variables and functions */
 scalar_t__ ARPHRD_ETHER ; 
 int EFAULT ; 
 int EINVAL ; 
 int ENOBUFS ; 
 int /*<<< orphan*/  IFNAMSIZ ; 
 scalar_t__ IF_GET_PROTO ; 
 scalar_t__ IF_PROTO_FR_ETH_PVC ; 
 scalar_t__ IF_PROTO_FR_PVC ; 
 scalar_t__ copy_to_user (int /*<<< orphan*/ ,TYPE_5__*,int) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int pvc_ioctl(struct net_device *dev, struct ifreq *ifr, int cmd)
{
	pvc_device *pvc = dev->ml_priv;
	fr_proto_pvc_info info;

	if (ifr->ifr_settings.type == IF_GET_PROTO) {
		if (dev->type == ARPHRD_ETHER)
			ifr->ifr_settings.type = IF_PROTO_FR_ETH_PVC;
		else
			ifr->ifr_settings.type = IF_PROTO_FR_PVC;

		if (ifr->ifr_settings.size < sizeof(info)) {
			/* data size wanted */
			ifr->ifr_settings.size = sizeof(info);
			return -ENOBUFS;
		}

		info.dlci = pvc->dlci;
		memcpy(info.master, pvc->frad->name, IFNAMSIZ);
		if (copy_to_user(ifr->ifr_settings.ifs_ifsu.fr_pvc_info,
				 &info, sizeof(info)))
			return -EFAULT;
		return 0;
	}

	return -EINVAL;
}