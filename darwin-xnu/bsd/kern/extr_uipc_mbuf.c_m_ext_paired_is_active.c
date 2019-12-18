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

/* Variables and functions */
 scalar_t__ MBUF_IS_PAIRED (struct mbuf*) ; 
 scalar_t__ MEXT_MINREF (struct mbuf*) ; 
 scalar_t__ MEXT_PREF (struct mbuf*) ; 

int
m_ext_paired_is_active(struct mbuf *m)
{
	return (MBUF_IS_PAIRED(m) ? (MEXT_PREF(m) > MEXT_MINREF(m)) : 1);
}