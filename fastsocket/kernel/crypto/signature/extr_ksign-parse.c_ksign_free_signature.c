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
struct ksign_signature {struct ksign_signature* unhashed_data; struct ksign_signature* hashed_data; int /*<<< orphan*/ * data; } ;

/* Variables and functions */
 int DSA_NSIG ; 
 int /*<<< orphan*/  kfree (struct ksign_signature*) ; 
 int /*<<< orphan*/  mpi_free (int /*<<< orphan*/ ) ; 

void ksign_free_signature(struct ksign_signature *sig)
{
	int i;

	if (sig) {
		for (i = 0; i < DSA_NSIG; i++)
			mpi_free(sig->data[i]);
		kfree(sig->hashed_data);
		kfree(sig->unhashed_data);
		kfree(sig);
	}
}