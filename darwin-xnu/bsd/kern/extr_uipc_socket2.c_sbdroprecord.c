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
struct sockbuf {struct mbuf* sb_mb; } ;
struct mbuf {struct mbuf* m_nextpkt; } ;

/* Variables and functions */
 int /*<<< orphan*/  EV_RWBYTES ; 
 int /*<<< orphan*/  MFREE (struct mbuf*,struct mbuf*) ; 
 int /*<<< orphan*/  SB_EMPTY_FIXUP (struct sockbuf*) ; 
 int /*<<< orphan*/  postevent (int /*<<< orphan*/ ,struct sockbuf*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sbfree (struct sockbuf*,struct mbuf*) ; 

void
sbdroprecord(struct sockbuf *sb)
{
	struct mbuf *m, *mn;

	m = sb->sb_mb;
	if (m) {
		sb->sb_mb = m->m_nextpkt;
		do {
			sbfree(sb, m);
			MFREE(m, mn);
			m = mn;
		} while (m);
	}
	SB_EMPTY_FIXUP(sb);
	postevent(0, sb, EV_RWBYTES);
}