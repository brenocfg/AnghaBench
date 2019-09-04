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
typedef  int /*<<< orphan*/  u_int16_t ;
typedef  TYPE_2__* mbuf_t ;
typedef  int /*<<< orphan*/  errno_t ;
struct TYPE_4__ {int /*<<< orphan*/  vlan_tag; int /*<<< orphan*/  csum_flags; } ;
struct TYPE_5__ {TYPE_1__ m_pkthdr; } ;

/* Variables and functions */
 int /*<<< orphan*/  CSUM_VLAN_TAG_VALID ; 

errno_t
mbuf_set_vlan_tag(
	mbuf_t mbuf,
	u_int16_t vlan)
{
	mbuf->m_pkthdr.csum_flags |= CSUM_VLAN_TAG_VALID;
	mbuf->m_pkthdr.vlan_tag = vlan;

	return (0);
}