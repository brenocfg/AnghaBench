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
 int /*<<< orphan*/  MLEN ; 
 int /*<<< orphan*/  MTOD (struct mbuf*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  _MGET (struct mbuf*,int,int) ; 
 int /*<<< orphan*/  bzero (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  caddr_t ; 

struct mbuf *
m_getclr(int wait, int type)
{
	struct mbuf *m;

	_MGET(m, wait, type);
	if (m != NULL)
		bzero(MTOD(m, caddr_t), MLEN);
	return (m);
}