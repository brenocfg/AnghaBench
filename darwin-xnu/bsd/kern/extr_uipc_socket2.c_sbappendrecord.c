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
struct sockbuf {int sb_flags; struct mbuf* sb_mbtail; struct mbuf* sb_lastrecord; struct mbuf* sb_mb; int /*<<< orphan*/  sb_so; } ;
struct mbuf {int m_flags; struct mbuf* m_next; struct mbuf* m_nextpkt; scalar_t__ m_len; } ;

/* Variables and functions */
 int EJUSTRETURN ; 
 int M_EOR ; 
 int M_SKIPCFIL ; 
 int /*<<< orphan*/  SBLASTRECORDCHK (struct sockbuf*,char*) ; 
 int SB_DROP ; 
 int SB_RECV ; 
 int SB_UNIX ; 
 int cfil_sock_data_in (int /*<<< orphan*/ ,int /*<<< orphan*/ *,struct mbuf*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  m_freem (struct mbuf*) ; 
 int /*<<< orphan*/  sballoc (struct sockbuf*,struct mbuf*) ; 
 int /*<<< orphan*/  sbcompress (struct sockbuf*,struct mbuf*,struct mbuf*) ; 
 int sbspace (struct sockbuf*) ; 
 int sflt_data_in (int /*<<< orphan*/ ,int /*<<< orphan*/ *,struct mbuf**,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sock_data_filt_flag_record ; 

int
sbappendrecord(struct sockbuf *sb, struct mbuf *m0)
{
	struct mbuf *m;
	int space = 0;

	if (m0 == NULL || (sb->sb_flags & SB_DROP)) {
		if (m0 != NULL)
			m_freem(m0);
		return (0);
	}

	for (m = m0; m != NULL; m = m->m_next)
		space += m->m_len;

	if (space > sbspace(sb) && !(sb->sb_flags & SB_UNIX)) {
		m_freem(m0);
		return (0);
	}

	if (sb->sb_flags & SB_RECV && !(m0 && m0->m_flags & M_SKIPCFIL)) {
		int error = sflt_data_in(sb->sb_so, NULL, &m0, NULL,
		    sock_data_filt_flag_record);

#if CONTENT_FILTER
		if (error == 0)
			error = cfil_sock_data_in(sb->sb_so, NULL, m0, NULL, 0);
#endif /* CONTENT_FILTER */

		if (error != 0) {
			SBLASTRECORDCHK(sb, "sbappendrecord 1");
			if (error != EJUSTRETURN)
				m_freem(m0);
			return (0);
		}
	} else if (m0) {
		m0->m_flags &= ~M_SKIPCFIL;
	}

	/*
	 * Note this permits zero length records.
	 */
	sballoc(sb, m0);
	SBLASTRECORDCHK(sb, "sbappendrecord 2");
	if (sb->sb_lastrecord != NULL) {
		sb->sb_lastrecord->m_nextpkt = m0;
	} else {
		sb->sb_mb = m0;
	}
	sb->sb_lastrecord = m0;
	sb->sb_mbtail = m0;

	m = m0->m_next;
	m0->m_next = 0;
	if (m && (m0->m_flags & M_EOR)) {
		m0->m_flags &= ~M_EOR;
		m->m_flags |= M_EOR;
	}
	sbcompress(sb, m, m0);
	SBLASTRECORDCHK(sb, "sbappendrecord 3");
	return (1);
}