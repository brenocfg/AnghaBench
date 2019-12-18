#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int count; float threshold; float* alpha; TYPE_2__* feature; } ;
typedef  TYPE_1__ ccv_bbf_stage_classifier_t ;
struct TYPE_5__ {int size; int /*<<< orphan*/ * nz; int /*<<< orphan*/ * ny; int /*<<< orphan*/ * nx; int /*<<< orphan*/ * pz; int /*<<< orphan*/ * py; int /*<<< orphan*/ * px; } ;
typedef  TYPE_2__ ccv_bbf_feature_t ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 scalar_t__ ccmalloc (int) ; 
 int /*<<< orphan*/  fclose (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * fopen (char const*,char*) ; 
 int fscanf (int /*<<< orphan*/ *,char*,int*,...) ; 

__attribute__((used)) static int _ccv_read_bbf_stage_classifier(const char* file, ccv_bbf_stage_classifier_t* classifier)
{
	FILE* r = fopen(file, "r");
	if (r == 0) return -1;
	int stat = 0;
	stat |= fscanf(r, "%d", &classifier->count);
	union { float fl; int i; } fli;
	stat |= fscanf(r, "%d", &fli.i);
	classifier->threshold = fli.fl;
	classifier->feature = (ccv_bbf_feature_t*)ccmalloc(classifier->count * sizeof(ccv_bbf_feature_t));
	classifier->alpha = (float*)ccmalloc(classifier->count * 2 * sizeof(float));
	int i, j;
	for (i = 0; i < classifier->count; i++)
	{
		stat |= fscanf(r, "%d", &classifier->feature[i].size);
		for (j = 0; j < classifier->feature[i].size; j++)
		{
			stat |= fscanf(r, "%d %d %d", &classifier->feature[i].px[j], &classifier->feature[i].py[j], &classifier->feature[i].pz[j]);
			stat |= fscanf(r, "%d %d %d", &classifier->feature[i].nx[j], &classifier->feature[i].ny[j], &classifier->feature[i].nz[j]);
		}
		union { float fl; int i; } flia, flib;
		stat |= fscanf(r, "%d %d", &flia.i, &flib.i);
		classifier->alpha[i * 2] = flia.fl;
		classifier->alpha[i * 2 + 1] = flib.fl;
	}
	fclose(r);
	return 0;
}