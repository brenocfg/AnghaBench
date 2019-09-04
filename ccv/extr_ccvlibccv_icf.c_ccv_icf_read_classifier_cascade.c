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
typedef  int /*<<< orphan*/  ccv_icf_classifier_cascade_t ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int /*<<< orphan*/  _ccv_icf_read_classifier_cascade_with_fd (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ ccmalloc (int) ; 
 int /*<<< orphan*/  fclose (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * fopen (char const*,char*) ; 

ccv_icf_classifier_cascade_t* ccv_icf_read_classifier_cascade(const char* filename)
{
	FILE* r = fopen(filename, "r");
	ccv_icf_classifier_cascade_t* cascade = 0;
	if (r)
	{
		cascade = (ccv_icf_classifier_cascade_t*)ccmalloc(sizeof(ccv_icf_classifier_cascade_t));
		_ccv_icf_read_classifier_cascade_with_fd(r, cascade);
		fclose(r);
	}
	return cascade;
}