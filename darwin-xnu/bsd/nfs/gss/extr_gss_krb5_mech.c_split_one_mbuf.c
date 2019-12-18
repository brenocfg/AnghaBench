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
 scalar_t__ EINVAL ; 
 int MBUF_PKTHDR ; 
 int /*<<< orphan*/  MBUF_WAITOK ; 
 int mbuf_flags (int /*<<< orphan*/ *) ; 
 size_t mbuf_len (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * mbuf_next (int /*<<< orphan*/ *) ; 
 scalar_t__ mbuf_setflags_mask (int /*<<< orphan*/ *,int,int) ; 
 int /*<<< orphan*/  mbuf_setnext (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ mbuf_split (int /*<<< orphan*/ *,size_t,int /*<<< orphan*/ ,int /*<<< orphan*/ **) ; 

__attribute__((used)) static errno_t
split_one_mbuf(mbuf_t mb, size_t offset, mbuf_t *nmb, int join)
{
	errno_t error;

	*nmb = mb;
	/* We don't have an mbuf or we're alread on an mbuf boundary */
	if (mb == NULL || offset == 0)
		return (0);

	/* If the mbuf length is offset then the next mbuf is the one we want */
	if (mbuf_len(mb) == offset) {
		*nmb = mbuf_next(mb);
		if (!join)
			mbuf_setnext(mb, NULL);
		return (0);
	}

	if (offset > mbuf_len(mb))
		return (EINVAL);

	error = mbuf_split(mb, offset, MBUF_WAITOK, nmb);
	if (error)
		return (error);

	if (mbuf_flags(*nmb) & MBUF_PKTHDR) {
		/* We don't want to copy the pkthdr. mbuf_split does that. */
		error = mbuf_setflags_mask(*nmb, ~MBUF_PKTHDR, MBUF_PKTHDR);
	}

	if (join)
		/* Join the chain again */
		mbuf_setnext(mb, *nmb);

	return (0);
}