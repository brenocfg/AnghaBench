#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  ushort_t ;
typedef  int /*<<< orphan*/  ctf_helem_t ;
struct TYPE_3__ {int h_nbuckets; int h_nelems; int /*<<< orphan*/ * h_chains; int /*<<< orphan*/ * h_buckets; } ;
typedef  TYPE_1__ ctf_hash_t ;

/* Variables and functions */
 int /*<<< orphan*/  ctf_free (int /*<<< orphan*/ *,int) ; 

void
ctf_hash_destroy(ctf_hash_t *hp)
{
	if (hp->h_buckets != NULL && hp->h_nbuckets != 1) {
		ctf_free(hp->h_buckets, sizeof (ushort_t) * hp->h_nbuckets);
		hp->h_buckets = NULL;
	}

	if (hp->h_chains != NULL) {
		ctf_free(hp->h_chains, sizeof (ctf_helem_t) * hp->h_nelems);
		hp->h_chains = NULL;
	}
}