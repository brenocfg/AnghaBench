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
typedef  scalar_t__ errno_t ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int) ; 
 size_t gss_mbuf_len (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 size_t mbuf_len (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * mbuf_next (int /*<<< orphan*/ *) ; 
 scalar_t__ split_one_mbuf (int /*<<< orphan*/ *,size_t,int /*<<< orphan*/ **,int) ; 

errno_t
gss_normalize_mbuf(mbuf_t chain, size_t offset, size_t *subchain_length, mbuf_t *subchain, mbuf_t *tail, int join)
{
	size_t length = *subchain_length ? *subchain_length : ~0;
	size_t len;
	mbuf_t mb, nmb;
	errno_t error;

	if (tail == NULL)
		tail = &nmb;
	*tail = NULL;
	*subchain = NULL;

	for (len = offset, mb = chain; mb && len > mbuf_len(mb); mb = mbuf_next(mb))
			len -= mbuf_len(mb);

	/* if we don't have offset bytes just return */
	if (mb == NULL)
		return (0);

	error = split_one_mbuf(mb, len, subchain, join);
	if (error)
		return (error);

	assert(subchain != NULL && *subchain != NULL);
	assert(offset == 0 ? mb == *subchain : 1);

	len = gss_mbuf_len(*subchain, 0);
	length =  (length > len) ? len : length;
	*subchain_length = length;

	for (len = length, mb = *subchain; mb && len > mbuf_len(mb); mb = mbuf_next(mb))
		len -= mbuf_len(mb);

	error = split_one_mbuf(mb, len, tail, join);

	return (error);
}