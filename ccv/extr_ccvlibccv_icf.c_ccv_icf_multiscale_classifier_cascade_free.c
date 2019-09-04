#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int count; TYPE_1__* cascade; } ;
typedef  TYPE_2__ ccv_icf_multiscale_classifier_cascade_t ;
struct TYPE_5__ {TYPE_2__* weak_classifiers; } ;

/* Variables and functions */
 int /*<<< orphan*/  ccfree (TYPE_2__*) ; 

void ccv_icf_multiscale_classifier_cascade_free(ccv_icf_multiscale_classifier_cascade_t* classifier)
{
	int i;
	for (i = 0; i < classifier->count; i++)
		ccfree(classifier->cascade[i].weak_classifiers);
	ccfree(classifier);
}