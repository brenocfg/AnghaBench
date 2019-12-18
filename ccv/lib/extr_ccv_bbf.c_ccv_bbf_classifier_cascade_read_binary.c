#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int count; int threshold; int* feature; float* alpha; } ;
typedef  TYPE_2__ ccv_bbf_stage_classifier_t ;
typedef  int ccv_bbf_feature_t ;
struct TYPE_5__ {int width; int height; } ;
struct TYPE_7__ {int count; TYPE_2__* stage_classifier; TYPE_1__ size; } ;
typedef  TYPE_3__ ccv_bbf_classifier_cascade_t ;

/* Variables and functions */
 scalar_t__ ccmalloc (int) ; 
 int /*<<< orphan*/  memcpy (int*,char*,int) ; 

ccv_bbf_classifier_cascade_t* ccv_bbf_classifier_cascade_read_binary(char* s)
{
	int i;
	ccv_bbf_classifier_cascade_t* cascade = (ccv_bbf_classifier_cascade_t*)ccmalloc(sizeof(ccv_bbf_classifier_cascade_t));
	memcpy(&cascade->count, s, sizeof(cascade->count)); s += sizeof(cascade->count);
	memcpy(&cascade->size.width, s, sizeof(cascade->size.width)); s += sizeof(cascade->size.width);
	memcpy(&cascade->size.height, s, sizeof(cascade->size.height)); s += sizeof(cascade->size.height);
	ccv_bbf_stage_classifier_t* classifier = cascade->stage_classifier = (ccv_bbf_stage_classifier_t*)ccmalloc(cascade->count * sizeof(ccv_bbf_stage_classifier_t));
	for (i = 0; i < cascade->count; i++, classifier++)
	{
		memcpy(&classifier->count, s, sizeof(classifier->count)); s += sizeof(classifier->count);
		memcpy(&classifier->threshold, s, sizeof(classifier->threshold)); s += sizeof(classifier->threshold);
		classifier->feature = (ccv_bbf_feature_t*)ccmalloc(classifier->count * sizeof(ccv_bbf_feature_t));
		classifier->alpha = (float*)ccmalloc(classifier->count * 2 * sizeof(float));
		memcpy(classifier->feature, s, classifier->count * sizeof(ccv_bbf_feature_t)); s += classifier->count * sizeof(ccv_bbf_feature_t);
		memcpy(classifier->alpha, s, classifier->count * 2 * sizeof(float)); s += classifier->count * 2 * sizeof(float);
	}
	return cascade;

}