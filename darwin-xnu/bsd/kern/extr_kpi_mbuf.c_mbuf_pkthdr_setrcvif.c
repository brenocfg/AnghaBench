#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct ifnet {int dummy; } ;
typedef  TYPE_2__* mbuf_t ;
typedef  scalar_t__ ifnet_t ;
typedef  int /*<<< orphan*/  errno_t ;
struct TYPE_4__ {struct ifnet* rcvif; } ;
struct TYPE_5__ {TYPE_1__ m_pkthdr; } ;

/* Variables and functions */

errno_t
mbuf_pkthdr_setrcvif(mbuf_t mbuf, ifnet_t ifnet)
{
	/* May want to walk ifnet list to determine if interface is valid */
	mbuf->m_pkthdr.rcvif = (struct ifnet *)ifnet;
	return (0);
}