#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_6__ ;
typedef  struct TYPE_12__   TYPE_5__ ;
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_12__ {int pass; double* weigh; double threshold; TYPE_2__* features; } ;
typedef  TYPE_5__ ccv_icf_decision_tree_t ;
struct TYPE_11__ {int left; int top; int right; int bottom; } ;
struct TYPE_10__ {int width; int height; } ;
struct TYPE_13__ {int count; int grayscale; TYPE_5__* weak_classifiers; TYPE_4__ margin; TYPE_3__ size; } ;
typedef  TYPE_6__ ccv_icf_classifier_cascade_t ;
struct TYPE_9__ {int count; double beta; int* channel; double* alpha; TYPE_1__* sat; } ;
struct TYPE_8__ {int x; int y; } ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ *,char*,int,double,...) ; 

__attribute__((used)) static void _ccv_icf_write_classifier_cascade_with_fd(ccv_icf_classifier_cascade_t* cascade, FILE* w)
{
	int i, q;
	fprintf(w, "%d %d %d %d\n", cascade->count, cascade->size.width, cascade->size.height, cascade->grayscale);
	fprintf(w, "%d %d %d %d\n", cascade->margin.left, cascade->margin.top, cascade->margin.right, cascade->margin.bottom);
	for (i = 0; i < cascade->count; i++)
	{
		ccv_icf_decision_tree_t* weak_classifier = cascade->weak_classifiers + i;
		fprintf(w, "%u %a %a %a\n", weak_classifier->pass, weak_classifier->weigh[0], weak_classifier->weigh[1], weak_classifier->threshold);
		fprintf(w, "%d %a\n", weak_classifier->features[0].count, weak_classifier->features[0].beta);
		for (q = 0; q < weak_classifier->features[0].count; q++)
			fprintf(w, "%d %a\n%d %d %d %d\n", weak_classifier->features[0].channel[q], weak_classifier->features[0].alpha[q], weak_classifier->features[0].sat[q * 2].x, weak_classifier->features[0].sat[q * 2].y, weak_classifier->features[0].sat[q * 2 + 1].x, weak_classifier->features[0].sat[q * 2 + 1].y);
		if (weak_classifier->pass & 0x2)
		{
			fprintf(w, "%d %a\n", weak_classifier->features[1].count, weak_classifier->features[1].beta);
			for (q = 0; q < weak_classifier->features[1].count; q++)
				fprintf(w, "%d %a\n%d %d %d %d\n", weak_classifier->features[1].channel[q], weak_classifier->features[1].alpha[q], weak_classifier->features[1].sat[q * 2].x, weak_classifier->features[1].sat[q * 2].y, weak_classifier->features[1].sat[q * 2 + 1].x, weak_classifier->features[1].sat[q * 2 + 1].y);
		}
		if (weak_classifier->pass & 0x1)
		{
			fprintf(w, "%d %a\n", weak_classifier->features[2].count, weak_classifier->features[2].beta);
			for (q = 0; q < weak_classifier->features[2].count; q++)
				fprintf(w, "%d %a\n%d %d %d %d\n", weak_classifier->features[2].channel[q], weak_classifier->features[2].alpha[q], weak_classifier->features[2].sat[q * 2].x, weak_classifier->features[2].sat[q * 2].y, weak_classifier->features[2].sat[q * 2 + 1].x, weak_classifier->features[2].sat[q * 2 + 1].y);
		}
	}
}