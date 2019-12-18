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
 int /*<<< orphan*/ * m_pulldown (int /*<<< orphan*/ *,size_t,size_t,int*) ; 

errno_t
mbuf_pulldown(mbuf_t src, size_t *offset, size_t len, mbuf_t *location)
{
	/* Must set *location to NULL in failure case */
	int new_offset;
	*location = m_pulldown(src, *offset, len, &new_offset);
	*offset = new_offset;

	return (*location == NULL ? ENOMEM : 0);
}