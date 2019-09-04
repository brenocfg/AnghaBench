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
typedef  int /*<<< orphan*/ * mbuf_t ;
typedef  int /*<<< orphan*/  errno_t ;

/* Variables and functions */
 int /*<<< orphan*/  ENOMEM ; 
 int /*<<< orphan*/ * m_pullup (int /*<<< orphan*/ *,size_t) ; 

errno_t
mbuf_pullup(mbuf_t *mbuf, size_t len)
{
	/* Must set *mbuf to NULL in failure case */
	*mbuf = m_pullup(*mbuf, len);

	return (*mbuf == NULL ? ENOMEM : 0);
}