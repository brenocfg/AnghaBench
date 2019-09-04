#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int width; int height; } ;
struct TYPE_9__ {int count; TYPE_3__* stage_classifier; TYPE_1__ size; } ;
typedef  TYPE_4__ ccv_bbf_classifier_cascade_t ;
struct TYPE_8__ {int count; double threshold; double* alpha; TYPE_2__* feature; } ;
struct TYPE_7__ {int size; int* px; int* py; int* pz; int* nx; int* ny; int* nz; } ;

/* Variables and functions */
 int /*<<< orphan*/  printf (char*,...) ; 

void write_c(ccv_bbf_classifier_cascade_t* cascade)
{

	printf("ccv_bbf_classifier_cascade_t* ccv_bbf_read_classifier_cascade()\n"
		   "{\n"
		   "	ccv_bbf_classifier_cascade_t* cascade = (ccv_bbf_classifier_cascade_t*)malloc(sizeof(ccv_bbf_classifier_cascade_t));\n"
		   "	cascade->count = %d;\n"
		   "	cascade->size = ccv_size(%d, %d);\n"
		   "	cascade->stage_classifier = (ccv_bbf_stage_classifier_t*)malloc(cascade->count * sizeof(ccv_bbf_stage_classifier_t));\n",
			cascade->count, cascade->size.width, cascade->size.height);
	int i, j, k;
	for (i = 0; i < cascade->count; i++)
	{
		printf("	{\n");
		printf("		ccv_bbf_stage_classifier_t* classifier = cascade->stage_classifier + %d;\n", i);
		printf("		classifier->count = %d;\n"
			   "		classifier->threshold = %f;\n",
			   cascade->stage_classifier[i].count, cascade->stage_classifier[i].threshold);
		printf("		classifier->feature = (ccv_bbf_feature_t*)malloc(classifier->count * sizeof(ccv_bbf_feature_t));\n"
			   "		classifier->alpha = (float*)malloc(classifier->count * 2 * sizeof(float));\n");
		for (j = 0; j < cascade->stage_classifier[i].count; j++)
		{
			printf("		classifier->feature[%d].size = %d;\n",
				   j, cascade->stage_classifier[i].feature[j].size);
			for (k = 0; k < cascade->stage_classifier[i].feature[j].size; k++)
			{
				printf("		classifier->feature[%d].px[%d] = %d;\n"
					   "		classifier->feature[%d].py[%d] = %d;\n"
					   "		classifier->feature[%d].pz[%d] = %d;\n",
					   j, k, cascade->stage_classifier[i].feature[j].px[k],
					   j, k, cascade->stage_classifier[i].feature[j].py[k],
					   j, k, cascade->stage_classifier[i].feature[j].pz[k]);
				printf("		classifier->feature[%d].nx[%d] = %d;\n"
					   "		classifier->feature[%d].ny[%d] = %d;\n"
					   "		classifier->feature[%d].nz[%d] = %d;\n",
					   j, k, cascade->stage_classifier[i].feature[j].nx[k],
					   j, k, cascade->stage_classifier[i].feature[j].ny[k],
					   j, k, cascade->stage_classifier[i].feature[j].nz[k]);
			}
			printf("		classifier->alpha[%d] = %f;\n"
				   "		classifier->alpha[%d] = %f;\n",
				   j * 2, cascade->stage_classifier[i].alpha[j * 2], j * 2 + 1, cascade->stage_classifier[i].alpha[j * 2 + 1]);
		}
		printf("	}\n");
	}
	printf("	return cascade;\n}");
}