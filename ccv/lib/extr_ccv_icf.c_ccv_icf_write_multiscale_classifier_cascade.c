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
struct TYPE_3__ {int octave; int count; int grayscale; scalar_t__ cascade; } ;
typedef  TYPE_1__ ccv_icf_multiscale_classifier_cascade_t ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int /*<<< orphan*/  _ccv_icf_write_classifier_cascade_with_fd (scalar_t__,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fclose (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * fopen (char*,char*) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ *,char*,int,int,int) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,char const*,...) ; 

void ccv_icf_write_multiscale_classifier_cascade(ccv_icf_multiscale_classifier_cascade_t* classifier, const char* directory)
{
	char filename[1024];
	snprintf(filename, 1024, "%s/multiscale", directory);
	FILE* w = fopen(filename, "w+");
	fprintf(w, "%d %d %d\n", classifier->octave, classifier->count, classifier->grayscale);
	fclose(w);
	int i;
	for (i = 0; i < classifier->count; i++)
	{
		snprintf(filename, 1024, "%s/cascade-%d", directory, i + 1);
		w = fopen(filename, "w+");
		_ccv_icf_write_classifier_cascade_with_fd(classifier->cascade + i, w);
		fclose(w);
	}
}