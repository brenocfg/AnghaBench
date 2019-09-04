#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int fq_flags; scalar_t__ fq_bytes; } ;
typedef  TYPE_1__ fq_t ;

/* Variables and functions */
 int FQF_NEW_FLOW ; 
 int FQF_OLD_FLOW ; 
 int /*<<< orphan*/  VERIFY (int) ; 
 int /*<<< orphan*/  flowq_cache ; 
 int fq_empty (TYPE_1__*) ; 
 int /*<<< orphan*/  mcache_free (int /*<<< orphan*/ ,TYPE_1__*) ; 

void
fq_destroy(fq_t *fq)
{
	VERIFY(fq_empty(fq));
	VERIFY(!(fq->fq_flags & (FQF_NEW_FLOW | FQF_OLD_FLOW)));
	VERIFY(fq->fq_bytes == 0);
	mcache_free(flowq_cache, fq);
}