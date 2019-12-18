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
struct ifdevmtu {int dummy; } ;
struct ifreq {struct ifdevmtu ifr_devmtu; } ;
struct ifnet {int dummy; } ;
typedef  int /*<<< orphan*/  ifr ;

/* Variables and functions */
 int /*<<< orphan*/  SIOCGIFDEVMTU ; 
 int /*<<< orphan*/  bzero (struct ifreq*,int) ; 
 int ifnet_ioctl (struct ifnet*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct ifreq*) ; 

__attribute__((used)) static int
siocgifdevmtu(struct ifnet * ifp, struct ifdevmtu * ifdm_p)
{
    struct ifreq	ifr;
    int 		error;

    bzero(&ifr, sizeof(ifr));
    error = ifnet_ioctl(ifp, 0,SIOCGIFDEVMTU, &ifr);
    if (error == 0) {
	*ifdm_p = ifr.ifr_devmtu;
    }
    return (error);
}