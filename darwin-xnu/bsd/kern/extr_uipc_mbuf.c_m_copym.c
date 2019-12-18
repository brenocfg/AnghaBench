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
 int /*<<< orphan*/  M_COPYM_MOVE_HDR ; 
 struct mbuf* m_copym_mode (struct mbuf*,int,int,int,int /*<<< orphan*/ ) ; 

struct mbuf *
m_copym(struct mbuf *m, int off0, int len, int wait)
{
	return (m_copym_mode(m, off0, len, wait, M_COPYM_MOVE_HDR));
}