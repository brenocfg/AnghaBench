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
struct TYPE_6__ {int count; int threshold; int* feature; int* alpha; } ;
typedef  TYPE_2__ ccv_bbf_stage_classifier_t ;
typedef  int /*<<< orphan*/  ccv_bbf_feature_t ;
struct TYPE_5__ {int width; int height; } ;
struct TYPE_7__ {int count; TYPE_2__* stage_classifier; TYPE_1__ size; } ;
typedef  TYPE_3__ ccv_bbf_classifier_cascade_t ;

/* Variables and functions */
 int /*<<< orphan*/  memcpy (char*,int*,int) ; 

int ccv_bbf_classifier_cascade_write_binary(ccv_bbf_classifier_cascade_t* cascade, char* s, int slen)
{
	int i;
	int len = sizeof(cascade->count) + sizeof(cascade->size.width) + sizeof(cascade->size.height);
	ccv_bbf_stage_classifier_t* classifier = cascade->stage_classifier;
	for (i = 0; i < cascade->count; i++, classifier++)
		len += sizeof(classifier->count) + sizeof(classifier->threshold) + classifier->count * sizeof(ccv_bbf_feature_t) + classifier->count * 2 * sizeof(float);
	if (slen >= len)
	{
		memcpy(s, &cascade->count, sizeof(cascade->count)); s += sizeof(cascade->count);
		memcpy(s, &cascade->size.width, sizeof(cascade->size.width)); s += sizeof(cascade->size.width);
		memcpy(s, &cascade->size.height, sizeof(cascade->size.height)); s += sizeof(cascade->size.height);
		classifier = cascade->stage_classifier;
		for (i = 0; i < cascade->count; i++, classifier++)
		{
			memcpy(s, &classifier->count, sizeof(classifier->count)); s += sizeof(classifier->count);
			memcpy(s, &classifier->threshold, sizeof(classifier->threshold)); s += sizeof(classifier->threshold);
			memcpy(s, classifier->feature, classifier->count * sizeof(ccv_bbf_feature_t)); s += classifier->count * sizeof(ccv_bbf_feature_t);
			memcpy(s, classifier->alpha, classifier->count * 2 * sizeof(float)); s += classifier->count * 2 * sizeof(float);
		}
	}
	return len;
}