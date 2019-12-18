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
struct TYPE_2__ {int /*<<< orphan*/  sa_data; int /*<<< orphan*/  sa_len; int /*<<< orphan*/  sa_family; } ;
struct ifreq {TYPE_1__ ifr_addr; } ;
struct ifnet {int dummy; } ;
struct ether_addr {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  AF_UNSPEC ; 
 int /*<<< orphan*/  ETHER_ADDR_LEN ; 
 int /*<<< orphan*/  SIOCSIFLLADDR ; 
 int /*<<< orphan*/  ether_addr_copy (int /*<<< orphan*/ ,struct ether_addr const*) ; 
 int ifnet_ioctl (struct ifnet*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct ifreq*) ; 

__attribute__((used)) static int
if_siflladdr(struct ifnet * ifp, const struct ether_addr * ea_p)
{
    struct ifreq	ifr;

    /*
     * XXX setting the sa_len to ETHER_ADDR_LEN is wrong, but the driver
     * currently expects it that way
     */
    ifr.ifr_addr.sa_family = AF_UNSPEC;
    ifr.ifr_addr.sa_len = ETHER_ADDR_LEN;
    ether_addr_copy(ifr.ifr_addr.sa_data, ea_p);
    return (ifnet_ioctl(ifp, 0, SIOCSIFLLADDR, &ifr));
}