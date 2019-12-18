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
struct sockbuf {struct mbuf* sb_mb; struct mbuf* sb_lastrecord; } ;
struct mbuf {struct mbuf* m_nextpkt; } ;

/* Variables and functions */
 scalar_t__ VM_KERNEL_ADDRPERM (struct mbuf*) ; 
 int /*<<< orphan*/  panic (char*,char const*) ; 
 int /*<<< orphan*/  printf (char*,...) ; 

void
sblastrecordchk(struct sockbuf *sb, const char *where)
{
	struct mbuf *m = sb->sb_mb;

	while (m && m->m_nextpkt)
		m = m->m_nextpkt;

	if (m != sb->sb_lastrecord) {
		printf("sblastrecordchk: mb 0x%llx lastrecord 0x%llx "
		    "last 0x%llx\n",
		    (uint64_t)VM_KERNEL_ADDRPERM(sb->sb_mb),
		    (uint64_t)VM_KERNEL_ADDRPERM(sb->sb_lastrecord),
		    (uint64_t)VM_KERNEL_ADDRPERM(m));
		printf("packet chain:\n");
		for (m = sb->sb_mb; m != NULL; m = m->m_nextpkt)
			printf("\t0x%llx\n", (uint64_t)VM_KERNEL_ADDRPERM(m));
		panic("sblastrecordchk from %s", where);
	}
}