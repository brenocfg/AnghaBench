#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int octave; int count; int grayscale; int /*<<< orphan*/ * cascade; int /*<<< orphan*/  type; } ;
typedef  TYPE_1__ ccv_icf_multiscale_classifier_cascade_t ;
typedef  int /*<<< orphan*/  ccv_icf_classifier_cascade_t ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int /*<<< orphan*/  CCV_ICF_CLASSIFIER_TYPE_B ; 
 int /*<<< orphan*/  _ccv_icf_read_classifier_cascade_with_fd (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ ccmalloc (int) ; 
 int /*<<< orphan*/  fclose (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * fopen (char*,char*) ; 
 int /*<<< orphan*/  fscanf (int /*<<< orphan*/ *,char*,int*,int*,int*) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,char const*,...) ; 

ccv_icf_multiscale_classifier_cascade_t* ccv_icf_read_multiscale_classifier_cascade(const char* directory)
{
	char filename[1024];
	snprintf(filename, 1024, "%s/multiscale", directory);
	FILE* r = fopen(filename, "r");
	if (r)
	{
		int octave = 0, count = 0, grayscale = 0;
		fscanf(r, "%d %d %d", &octave, &count, &grayscale);
		fclose(r);
		ccv_icf_multiscale_classifier_cascade_t* classifier = (ccv_icf_multiscale_classifier_cascade_t*)ccmalloc(sizeof(ccv_icf_multiscale_classifier_cascade_t) + sizeof(ccv_icf_classifier_cascade_t) * count);
		classifier->type = CCV_ICF_CLASSIFIER_TYPE_B;
		classifier->octave = octave;
		classifier->count = count;
		classifier->grayscale = grayscale;
		classifier->cascade = (ccv_icf_classifier_cascade_t*)(classifier + 1);
		int i;
		for (i = 0; i < count; i++)
		{
			snprintf(filename, 1024, "%s/cascade-%d", directory, i + 1);
			r = fopen(filename, "r");
			if (r)
			{
				ccv_icf_classifier_cascade_t* cascade = classifier->cascade + i;
				_ccv_icf_read_classifier_cascade_with_fd(r, cascade);
				fclose(r);
			}
		}
		return classifier;
	}
	return 0;
}