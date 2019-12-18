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
typedef  int /*<<< orphan*/  uint64_t ;
struct mbuf {int dummy; } ;
struct m_tag {scalar_t__ m_tag_id; scalar_t__ m_tag_type; } ;
struct dn_pkt_tag {int dummy; } ;

/* Variables and functions */
 scalar_t__ KERNEL_MODULE_TAG_ID ; 
 scalar_t__ KERNEL_TAG_TYPE_DUMMYNET ; 
 scalar_t__ VM_KERNEL_ADDRPERM (struct mbuf*) ; 
 struct m_tag* m_tag_first (struct mbuf*) ; 
 int /*<<< orphan*/  panic (char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct dn_pkt_tag *
dn_tag_get(struct mbuf *m)
{
    struct m_tag *mtag = m_tag_first(m);

    if (!(mtag != NULL &&
          mtag->m_tag_id == KERNEL_MODULE_TAG_ID &&
          mtag->m_tag_type == KERNEL_TAG_TYPE_DUMMYNET))
	panic("packet on dummynet queue w/o dummynet tag: 0x%llx",
	    (uint64_t)VM_KERNEL_ADDRPERM(m));

    return (struct dn_pkt_tag *)(mtag+1);
}