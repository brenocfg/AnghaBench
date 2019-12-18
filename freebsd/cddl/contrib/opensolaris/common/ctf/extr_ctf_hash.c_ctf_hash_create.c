#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int h_nbuckets; int h_nelems; int h_free; struct TYPE_6__* h_chains; struct TYPE_6__* h_buckets; } ;
typedef  TYPE_1__ ushort_t ;
typedef  scalar_t__ ulong_t ;
typedef  int /*<<< orphan*/  ctf_helem_t ;
typedef  TYPE_1__ ctf_hash_t ;

/* Variables and functions */
 int EAGAIN ; 
 int EOVERFLOW ; 
 scalar_t__ USHRT_MAX ; 
 scalar_t__ _CTF_EMPTY ; 
 int /*<<< orphan*/  bzero (TYPE_1__*,int) ; 
 void* ctf_alloc (int) ; 
 int /*<<< orphan*/  ctf_hash_destroy (TYPE_1__*) ; 

int
ctf_hash_create(ctf_hash_t *hp, ulong_t nelems)
{
	if (nelems > USHRT_MAX)
		return (EOVERFLOW);

	/*
	 * If the hash table is going to be empty, don't bother allocating any
	 * memory and make the only bucket point to a zero so lookups fail.
	 */
	if (nelems == 0) {
		bzero(hp, sizeof (ctf_hash_t));
		hp->h_buckets = (ushort_t *)_CTF_EMPTY;
		hp->h_nbuckets = 1;
		return (0);
	}

	hp->h_nbuckets = 211;		/* use a prime number of hash buckets */
	hp->h_nelems = nelems + 1;	/* we use index zero as a sentinel */
	hp->h_free = 1;			/* first free element is index 1 */

	hp->h_buckets = ctf_alloc(sizeof (ushort_t) * hp->h_nbuckets);
	hp->h_chains = ctf_alloc(sizeof (ctf_helem_t) * hp->h_nelems);

	if (hp->h_buckets == NULL || hp->h_chains == NULL) {
		ctf_hash_destroy(hp);
		return (EAGAIN);
	}

	bzero(hp->h_buckets, sizeof (ushort_t) * hp->h_nbuckets);
	bzero(hp->h_chains, sizeof (ctf_helem_t) * hp->h_nelems);

	return (0);
}