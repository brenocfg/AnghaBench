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
typedef  int u_int32_t ;
struct sockbuf {int sb_mbcnt; int sb_flags; int /*<<< orphan*/  sb_so; int /*<<< orphan*/  sb_ctl; int /*<<< orphan*/  sb_cc; } ;
struct TYPE_2__ {int ext_size; } ;
struct mbuf {scalar_t__ m_type; int m_flags; scalar_t__ m_len; TYPE_1__ m_ext; } ;

/* Variables and functions */
 scalar_t__ MSIZE ; 
 int MSIZESHIFT ; 
 scalar_t__ MT_DATA ; 
 scalar_t__ MT_HEADER ; 
 scalar_t__ MT_OOBDATA ; 
 int M_EXT ; 
 int /*<<< orphan*/  OSAddAtomic (int,scalar_t__*) ; 
 int SB_SNDBYTE_CNT ; 
 int /*<<< orphan*/  VERIFY (int) ; 
 int /*<<< orphan*/  inp_incr_sndbytes_total (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  inp_incr_sndbytes_unsent (int /*<<< orphan*/ ,scalar_t__) ; 
 scalar_t__ total_sbmb_cnt ; 
 scalar_t__ total_sbmb_cnt_peak ; 

void
sballoc(struct sockbuf *sb, struct mbuf *m)
{
	u_int32_t cnt = 1;
	sb->sb_cc += m->m_len;
	if (m->m_type != MT_DATA && m->m_type != MT_HEADER &&
	    m->m_type != MT_OOBDATA)
		sb->sb_ctl += m->m_len;
	sb->sb_mbcnt += MSIZE;

	if (m->m_flags & M_EXT) {
		sb->sb_mbcnt += m->m_ext.ext_size;
		cnt += (m->m_ext.ext_size >> MSIZESHIFT);
	}
	OSAddAtomic(cnt, &total_sbmb_cnt);
	VERIFY(total_sbmb_cnt > 0);
	if (total_sbmb_cnt > total_sbmb_cnt_peak)
		total_sbmb_cnt_peak = total_sbmb_cnt;

	/*
	 * If data is being added to the send socket buffer,
	 * update the send byte count
	 */
	if (sb->sb_flags & SB_SNDBYTE_CNT) {
		inp_incr_sndbytes_total(sb->sb_so, m->m_len);
		inp_incr_sndbytes_unsent(sb->sb_so, m->m_len);
	}
}