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
typedef  struct mbuf* mbuf_t ;
typedef  int /*<<< orphan*/  mbuf_how_t ;
typedef  scalar_t__ errno_t ;

/* Variables and functions */
 scalar_t__ EINVAL ; 
 scalar_t__ ENOBUFS ; 
 scalar_t__ ENOMEM ; 
 struct mbuf* m_allocpacket_internal (unsigned int*,size_t,unsigned int*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 

errno_t
mbuf_allocpacket(mbuf_how_t how, size_t packetlen, unsigned int *maxchunks,
    mbuf_t *mbuf)
{
	errno_t error;
	struct mbuf *m;
	unsigned int numpkts = 1;
	unsigned int numchunks = maxchunks ? *maxchunks : 0;

	if (packetlen == 0) {
		error = EINVAL;
		goto out;
	}
	m = m_allocpacket_internal(&numpkts, packetlen,
	    maxchunks ? &numchunks : NULL, how, 1, 0);
	if (m == 0) {
		if (maxchunks && *maxchunks && numchunks > *maxchunks)
			error = ENOBUFS;
		else
			error = ENOMEM;
	} else {
		if (maxchunks)
			*maxchunks = numchunks;
		error = 0;
		*mbuf = m;
	}
out:
	return (error);
}