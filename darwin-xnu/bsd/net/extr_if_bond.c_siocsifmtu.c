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
struct ifreq {int ifr_mtu; } ;
struct ifnet {int dummy; } ;
typedef  int /*<<< orphan*/  ifr ;

/* Variables and functions */
 int /*<<< orphan*/  SIOCSIFMTU ; 
 int /*<<< orphan*/  bzero (struct ifreq*,int) ; 
 int ifnet_ioctl (struct ifnet*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct ifreq*) ; 

__attribute__((used)) static int
siocsifmtu(struct ifnet * ifp, int mtu)
{
    struct ifreq	ifr;

    bzero(&ifr, sizeof(ifr));
    ifr.ifr_mtu = mtu;
    return (ifnet_ioctl(ifp, 0, SIOCSIFMTU, &ifr));
}