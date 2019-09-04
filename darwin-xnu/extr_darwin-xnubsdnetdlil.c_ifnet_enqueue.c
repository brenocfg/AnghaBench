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
struct mbuf {int dummy; } ;
struct ifnet {int dummy; } ;
typedef  int /*<<< orphan*/  errno_t ;
typedef  int /*<<< orphan*/  boolean_t ;

/* Variables and functions */
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  ifnet_enqueue_mbuf (struct ifnet*,struct mbuf*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

errno_t
ifnet_enqueue(struct ifnet *ifp, struct mbuf *m)
{
	boolean_t pdrop;
	return (ifnet_enqueue_mbuf(ifp, m, TRUE, &pdrop));
}