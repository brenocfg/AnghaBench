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
struct qfq_if {struct qfq_group** qif_groups; } ;
struct qfq_group {int dummy; } ;
typedef  int /*<<< orphan*/  pktsched_bitmap_t ;

/* Variables and functions */
 int QFQ_MAX_INDEX ; 
 int /*<<< orphan*/  VERIFY (int) ; 
 int pktsched_ffs (int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline struct qfq_group *
qfq_ffs(struct qfq_if *qif, pktsched_bitmap_t bitmap)
{
	int index = pktsched_ffs(bitmap) - 1;	/* zero-based */
	VERIFY(index >= 0 && index <= QFQ_MAX_INDEX &&
	    qif->qif_groups[index] != NULL);
	return (qif->qif_groups[index]);
}