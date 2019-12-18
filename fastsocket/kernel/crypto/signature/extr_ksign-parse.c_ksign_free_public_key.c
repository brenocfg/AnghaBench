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
struct ksign_public_key {int /*<<< orphan*/ * pkey; } ;

/* Variables and functions */
 int DSA_NPKEY ; 
 int /*<<< orphan*/  kfree (struct ksign_public_key*) ; 
 int /*<<< orphan*/  mpi_free (int /*<<< orphan*/ ) ; 

void ksign_free_public_key(struct ksign_public_key *pk)
{
	int i;

	if (pk) {
		for (i = 0; i < DSA_NPKEY; i++)
			mpi_free(pk->pkey[i]);
		kfree(pk);
	}
}