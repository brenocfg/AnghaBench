#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {struct TYPE_4__* weak_classifiers; } ;
typedef  TYPE_1__ ccv_icf_classifier_cascade_t ;

/* Variables and functions */
 int /*<<< orphan*/  ccfree (TYPE_1__*) ; 

void ccv_icf_classifier_cascade_free(ccv_icf_classifier_cascade_t* classifier)
{
	ccfree(classifier->weak_classifiers);
	ccfree(classifier);
}