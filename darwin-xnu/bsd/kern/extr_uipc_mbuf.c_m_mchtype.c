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
struct mbuf {int m_type; } ;

/* Variables and functions */
 int /*<<< orphan*/  mtype_stat_dec (int) ; 
 int /*<<< orphan*/  mtype_stat_inc (int) ; 

void
m_mchtype(struct mbuf *m, int t)
{
	mtype_stat_inc(t);
	mtype_stat_dec(m->m_type);
	(m)->m_type = t;
}