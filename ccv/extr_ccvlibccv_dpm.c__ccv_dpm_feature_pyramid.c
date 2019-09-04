#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_1__ ;

/* Type definitions */
struct TYPE_12__ {double rows; double cols; } ;
typedef  TYPE_1__ ccv_dense_matrix_t ;

/* Variables and functions */
 int CCV_DPM_WINDOW_SIZE ; 
 int /*<<< orphan*/  CCV_INTER_AREA ; 
 int /*<<< orphan*/  ccv_hog (TYPE_1__*,TYPE_1__**,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  ccv_matrix_free (TYPE_1__*) ; 
 int /*<<< orphan*/  ccv_resample (TYPE_1__*,TYPE_1__**,int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ccv_sample_down (TYPE_1__*,TYPE_1__**,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (TYPE_1__**,int /*<<< orphan*/ ,int) ; 
 double pow (double,int) ; 

__attribute__((used)) static void _ccv_dpm_feature_pyramid(ccv_dense_matrix_t* a, ccv_dense_matrix_t** pyr, int scale_upto, int interval)
{
	int next = interval + 1;
	double scale = pow(2.0, 1.0 / (interval + 1.0));
	memset(pyr, 0, (scale_upto + next * 2) * sizeof(ccv_dense_matrix_t*));
	pyr[next] = a;
	int i;
	for (i = 1; i <= interval; i++)
		ccv_resample(pyr[next], &pyr[next + i], 0, (int)(pyr[next]->rows / pow(scale, i)), (int)(pyr[next]->cols / pow(scale, i)), CCV_INTER_AREA);
	for (i = next; i < scale_upto + next; i++)
		ccv_sample_down(pyr[i], &pyr[i + next], 0, 0, 0);
	ccv_dense_matrix_t* hog;
	/* a more efficient way to generate up-scaled hog (using smaller size) */
	for (i = 0; i < next; i++)
	{
		hog = 0;
		ccv_hog(pyr[i + next], &hog, 0, 9, CCV_DPM_WINDOW_SIZE / 2 /* this is */);
		pyr[i] = hog;
	}
	hog = 0;
	ccv_hog(pyr[next], &hog, 0, 9, CCV_DPM_WINDOW_SIZE);
	pyr[next] = hog;
	for (i = next + 1; i < scale_upto + next * 2; i++)
	{
		hog = 0;
		ccv_hog(pyr[i], &hog, 0, 9, CCV_DPM_WINDOW_SIZE);
		ccv_matrix_free(pyr[i]);
		pyr[i] = hog;
	}
}