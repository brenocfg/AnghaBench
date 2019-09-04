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
typedef  scalar_t__ mbuf_class_t ;

/* Variables and functions */
 int /*<<< orphan*/  LCK_MTX_ASSERT (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LCK_MTX_ASSERT_OWNED ; 
 scalar_t__ MC_BIGCL ; 
 scalar_t__ MC_CL ; 
 int /*<<< orphan*/  M_WAIT ; 
 int /*<<< orphan*/  VERIFY (int) ; 
 int /*<<< orphan*/  freelist_populate (scalar_t__,scalar_t__,int /*<<< orphan*/ ) ; 
 scalar_t__ m_minlimit (scalar_t__) ; 
 scalar_t__ m_total (scalar_t__) ; 
 int /*<<< orphan*/  mbuf_mlock ; 

__attribute__((used)) static void
freelist_init(mbuf_class_t class)
{
	LCK_MTX_ASSERT(mbuf_mlock, LCK_MTX_ASSERT_OWNED);

	VERIFY(class == MC_CL || class == MC_BIGCL);
	VERIFY(m_total(class) == 0);
	VERIFY(m_minlimit(class) > 0);

	while (m_total(class) < m_minlimit(class))
		(void) freelist_populate(class, m_minlimit(class), M_WAIT);

	VERIFY(m_total(class) >= m_minlimit(class));
}