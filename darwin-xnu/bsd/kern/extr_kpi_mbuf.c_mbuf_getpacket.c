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
typedef  scalar_t__ mbuf_how_t ;
typedef  int /*<<< orphan*/  errno_t ;

/* Variables and functions */
 int /*<<< orphan*/  ENOMEM ; 
 int /*<<< orphan*/  EWOULDBLOCK ; 
 scalar_t__ MBUF_WAITOK ; 
 int /*<<< orphan*/ * m_getpacket_how (scalar_t__) ; 

errno_t
mbuf_getpacket(mbuf_how_t how, mbuf_t *mbuf)
{
	/* Must set *mbuf to NULL in failure case */
	errno_t	error = 0;

	*mbuf = m_getpacket_how(how);

	if (*mbuf == NULL) {
		if (how == MBUF_WAITOK)
			error = ENOMEM;
		else
			error = EWOULDBLOCK;
	}

	return (error);
}