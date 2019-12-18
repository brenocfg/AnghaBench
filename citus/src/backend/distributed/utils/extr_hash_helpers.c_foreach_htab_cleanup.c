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
typedef  int /*<<< orphan*/  HASH_SEQ_STATUS ;

/* Variables and functions */
 int /*<<< orphan*/  hash_seq_term (int /*<<< orphan*/ *) ; 

void
foreach_htab_cleanup(void *var, HASH_SEQ_STATUS *status)
{
	if ((var) != NULL)
	{
		hash_seq_term(status);
	}
}