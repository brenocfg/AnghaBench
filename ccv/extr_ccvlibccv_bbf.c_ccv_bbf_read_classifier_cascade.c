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
typedef  int /*<<< orphan*/  ccv_bbf_stage_classifier_t ;
struct TYPE_4__ {int /*<<< orphan*/  height; int /*<<< orphan*/  width; } ;
struct TYPE_5__ {int count; int /*<<< orphan*/ * stage_classifier; TYPE_1__ size; } ;
typedef  TYPE_2__ ccv_bbf_classifier_cascade_t ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 scalar_t__ _ccv_read_bbf_stage_classifier (char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  assert (int) ; 
 scalar_t__ ccmalloc (int) ; 
 int /*<<< orphan*/  fclose (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * fopen (char*,char*) ; 
 int fscanf (int /*<<< orphan*/ *,char*,int*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sprintf (char*,char*,char const*,...) ; 

ccv_bbf_classifier_cascade_t* ccv_bbf_read_classifier_cascade(const char* directory)
{
	char buf[1024];
	sprintf(buf, "%s/cascade.txt", directory);
	int s, i;
	FILE* r = fopen(buf, "r");
	if (r == 0)
		return 0;
	ccv_bbf_classifier_cascade_t* cascade = (ccv_bbf_classifier_cascade_t*)ccmalloc(sizeof(ccv_bbf_classifier_cascade_t));
	s = fscanf(r, "%d %d %d", &cascade->count, &cascade->size.width, &cascade->size.height);
	assert(s > 0);
	cascade->stage_classifier = (ccv_bbf_stage_classifier_t*)ccmalloc(cascade->count * sizeof(ccv_bbf_stage_classifier_t));
	for (i = 0; i < cascade->count; i++)
	{
		sprintf(buf, "%s/stage-%d.txt", directory, i);
		if (_ccv_read_bbf_stage_classifier(buf, &cascade->stage_classifier[i]) < 0)
		{
			cascade->count = i;
			break;
		}
	}
	fclose(r);
	return cascade;
}