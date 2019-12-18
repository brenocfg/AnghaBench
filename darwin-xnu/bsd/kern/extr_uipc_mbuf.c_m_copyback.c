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
 int M_COPYBACK0_COPYBACK ; 
 int M_COPYBACK0_EXTEND ; 
 int /*<<< orphan*/  M_DONTWAIT ; 
 int m_copyback0 (struct mbuf**,int,int,void const*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  panic (char*) ; 

void
m_copyback(struct mbuf *m0, int off, int len, const void *cp)
{
#if DEBUG
	struct mbuf *origm = m0;
	int error;
#endif /* DEBUG */

	if (m0 == NULL)
		return;

#if DEBUG
	error =
#endif /* DEBUG */
	m_copyback0(&m0, off, len, cp,
	    M_COPYBACK0_COPYBACK | M_COPYBACK0_EXTEND, M_DONTWAIT);

#if DEBUG
	if (error != 0 || (m0 != NULL && origm != m0))
		panic("m_copyback");
#endif /* DEBUG */
}