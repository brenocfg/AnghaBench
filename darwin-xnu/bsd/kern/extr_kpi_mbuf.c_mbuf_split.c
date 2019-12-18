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
typedef  int /*<<< orphan*/  mbuf_how_t ;
typedef  int /*<<< orphan*/  errno_t ;

/* Variables and functions */
 int /*<<< orphan*/  ENOMEM ; 
 int /*<<< orphan*/ * m_split (int /*<<< orphan*/ *,size_t,int /*<<< orphan*/ ) ; 

errno_t
mbuf_split(mbuf_t src, size_t offset,
					mbuf_how_t how, mbuf_t *new_mbuf)
{
	/* Must set *new_mbuf to NULL in failure case */
	*new_mbuf = m_split(src, offset, how);

	return (*new_mbuf == NULL ? ENOMEM : 0);
}