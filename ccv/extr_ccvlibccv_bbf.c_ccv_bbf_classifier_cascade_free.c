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
struct TYPE_4__ {int count; struct TYPE_4__* stage_classifier; struct TYPE_4__* alpha; struct TYPE_4__* feature; } ;
typedef  TYPE_1__ ccv_bbf_classifier_cascade_t ;

/* Variables and functions */
 int /*<<< orphan*/  ccfree (TYPE_1__*) ; 

void ccv_bbf_classifier_cascade_free(ccv_bbf_classifier_cascade_t* cascade)
{
	int i;
	for (i = 0; i < cascade->count; ++i)
	{
		ccfree(cascade->stage_classifier[i].feature);
		ccfree(cascade->stage_classifier[i].alpha);
	}
	ccfree(cascade->stage_classifier);
	ccfree(cascade);
}