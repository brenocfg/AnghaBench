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
typedef  scalar_t__ mbuf_t ;

/* Variables and functions */
 scalar_t__ mbuf_next (scalar_t__) ; 
 int /*<<< orphan*/  mbuf_setnext (scalar_t__,scalar_t__) ; 

mbuf_t
gss_join_mbuf(mbuf_t head, mbuf_t body, mbuf_t tail)
{
	mbuf_t mb;

	for (mb = head; mb && mbuf_next(mb); mb = mbuf_next(mb))
		;
	if (mb)
		mbuf_setnext(mb, body);
	for (mb = body; mb && mbuf_next(mb); mb = mbuf_next(mb))
		;
	if (mb)
		mbuf_setnext(mb, tail);
	mb = head ? head : (body ? body : tail);
	return (mb);
}