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
struct TYPE_5__ {int count; struct TYPE_5__* classifiers; struct TYPE_5__* features; } ;
typedef  TYPE_1__ ccv_scd_stump_classifier_t ;
typedef  TYPE_1__ ccv_scd_classifier_cascade_t ;

/* Variables and functions */
 int /*<<< orphan*/  ccfree (TYPE_1__*) ; 

void ccv_scd_classifier_cascade_free(ccv_scd_classifier_cascade_t* cascade)
{
	int i;
	for (i = 0; i < cascade->count; i++)
	{
		ccv_scd_stump_classifier_t* classifier = cascade->classifiers + i;
		ccfree(classifier->features);
	}
	ccfree(cascade->classifiers);
	ccfree(cascade);
}