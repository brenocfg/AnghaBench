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
 struct mbuf* m_split0 (struct mbuf*,int,int,int) ; 

struct mbuf *
m_split(struct mbuf *m0, int len0, int wait)
{
	return (m_split0(m0, len0, wait, 1));
}