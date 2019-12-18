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
 struct mbuf* m_defrag_offset (struct mbuf*,int /*<<< orphan*/ ,int) ; 

struct mbuf *
m_defrag(struct mbuf *m0, int how)
{
	return (m_defrag_offset(m0, 0, how));
}