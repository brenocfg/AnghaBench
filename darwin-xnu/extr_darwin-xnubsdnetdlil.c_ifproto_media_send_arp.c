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
typedef  int /*<<< orphan*/  u_short ;
struct sockaddr_dl {int dummy; } ;
struct sockaddr {int dummy; } ;
struct ifnet {int dummy; } ;
typedef  int /*<<< orphan*/  errno_t ;

/* Variables and functions */
 int /*<<< orphan*/  ENXIO ; 

__attribute__((used)) static errno_t
ifproto_media_send_arp(struct ifnet *ifp, u_short arpop,
    const struct sockaddr_dl *sender_hw, const struct sockaddr *sender_proto,
    const struct sockaddr_dl *target_hw, const struct sockaddr *target_proto)
{
#pragma unused(ifp, arpop, sender_hw, sender_proto, target_hw, target_proto)
	return (ENXIO);
}