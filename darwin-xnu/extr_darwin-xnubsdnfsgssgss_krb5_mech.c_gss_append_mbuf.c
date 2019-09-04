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
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int /*<<< orphan*/ * mbuf_t ;
typedef  int /*<<< orphan*/  errno_t ;

/* Variables and functions */
 int /*<<< orphan*/  EINVAL ; 
 int /*<<< orphan*/  MBUF_WAITOK ; 
 int /*<<< orphan*/  mbuf_copyback (int /*<<< orphan*/ *,size_t,size_t,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ mbuf_len (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * mbuf_next (int /*<<< orphan*/ *) ; 

errno_t
gss_append_mbuf(mbuf_t chain, uint8_t *bytes, size_t size)
{
	size_t len = 0;
	mbuf_t mb;

	if (chain == NULL)
		return (EINVAL);

	for (mb = chain; mb; mb = mbuf_next(mb))
		len += mbuf_len(mb);

	return (mbuf_copyback(chain, len, size, bytes, MBUF_WAITOK));
}