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
struct zd1201 {int /*<<< orphan*/  ap; } ;
struct sockaddr {int /*<<< orphan*/  sa_data; } ;
struct net_device {int dummy; } ;
struct iw_request_info {int dummy; } ;

/* Variables and functions */
 int EOPNOTSUPP ; 
 int /*<<< orphan*/  ETH_ALEN ; 
 int /*<<< orphan*/  ZD1201_RID_AUTHENTICATESTA ; 
 int /*<<< orphan*/  memcpy (unsigned char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct zd1201* netdev_priv (struct net_device*) ; 
 int zd1201_setconfig (struct zd1201*,int /*<<< orphan*/ ,unsigned char*,int,int) ; 

__attribute__((used)) static int zd1201_auth_sta(struct net_device *dev,
    struct iw_request_info *info, struct sockaddr *sta, char *extra)
{
	struct zd1201 *zd = netdev_priv(dev);
	unsigned char buffer[10];

	if (!zd->ap)
		return -EOPNOTSUPP;

	memcpy(buffer, sta->sa_data, ETH_ALEN);
	*(short*)(buffer+6) = 0;	/* 0==success, 1==failure */
	*(short*)(buffer+8) = 0;

	return zd1201_setconfig(zd, ZD1201_RID_AUTHENTICATESTA, buffer, 10, 1);
}