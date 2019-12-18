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
struct whc_qset {int /*<<< orphan*/  remove_complete; } ;
struct whc {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  qset_free (struct whc*,struct whc_qset*) ; 
 int /*<<< orphan*/  wait_for_completion (int /*<<< orphan*/ *) ; 

void qset_delete(struct whc *whc, struct whc_qset *qset)
{
	wait_for_completion(&qset->remove_complete);
	qset_free(whc, qset);
}