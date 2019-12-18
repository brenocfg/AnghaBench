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
struct rtable {struct in_device* idev; struct inet_peer* peer; } ;
struct inet_peer {int dummy; } ;
struct in_device {int dummy; } ;
struct dst_entry {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  in_dev_put (struct in_device*) ; 
 int /*<<< orphan*/  inet_putpeer (struct inet_peer*) ; 

__attribute__((used)) static void ipv4_dst_destroy(struct dst_entry *dst)
{
	struct rtable *rt = (struct rtable *) dst;
	struct inet_peer *peer = rt->peer;
	struct in_device *idev = rt->idev;

	if (peer) {
		rt->peer = NULL;
		inet_putpeer(peer);
	}

	if (idev) {
		rt->idev = NULL;
		in_dev_put(idev);
	}
}