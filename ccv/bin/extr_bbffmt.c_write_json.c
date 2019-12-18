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
struct TYPE_8__ {int count; int /*<<< orphan*/ * alpha; TYPE_2__* feature; int /*<<< orphan*/  threshold; } ;
struct TYPE_7__ {int size; int* px; int* py; int* pz; int* nx; int* ny; int* nz; } ;

/* Variables and functions */
 int /*<<< orphan*/  printf (char*,...) ; 

void write_json(ccv_bbf_classifier_cascade_t* cascade)
{

	printf("{\"count\" : %d, \"width\" : %d, \"height\" : %d, \"stage_classifier\" : [",
		   cascade->count, cascade->size.width, cascade->size.height);
	int i, j, k;
	for (i = 0; i < cascade->count; i++)
	{
		printf("{\"count\":%d,\"threshold\":%le,\"feature\":[",
			   cascade->stage_classifier[i].count, cascade->stage_classifier[i].threshold);
		for (j = 0; j < cascade->stage_classifier[i].count; j++)
		{
			printf("{\"size\":%d,\"px\":[%d", cascade->stage_classifier[i].feature[j].size, cascade->stage_classifier[i].feature[j].px[0]);
			for (k = 1; k < cascade->stage_classifier[i].feature[j].size; k++)
				printf(",%d", cascade->stage_classifier[i].feature[j].px[k]);
			printf("],\"py\":[%d", cascade->stage_classifier[i].feature[j].py[0]);
			for (k = 1; k < cascade->stage_classifier[i].feature[j].size; k++)
				printf(",%d", cascade->stage_classifier[i].feature[j].py[k]);
			printf("],\"pz\":[%d", cascade->stage_classifier[i].feature[j].pz[0]);
			for (k = 1; k < cascade->stage_classifier[i].feature[j].size; k++)
				printf(",%d", cascade->stage_classifier[i].feature[j].pz[k]);
			printf("],\"nx\":[%d", cascade->stage_classifier[i].feature[j].nx[0]);
			for (k = 1; k < cascade->stage_classifier[i].feature[j].size; k++)
				printf(",%d", cascade->stage_classifier[i].feature[j].nx[k]);
			printf("],\"ny\":[%d", cascade->stage_classifier[i].feature[j].ny[0]);
			for (k = 1; k < cascade->stage_classifier[i].feature[j].size; k++)
				printf(",%d", cascade->stage_classifier[i].feature[j].ny[k]);
			printf("],\"nz\":[%d", cascade->stage_classifier[i].feature[j].nz[0]);
			for (k = 1; k < cascade->stage_classifier[i].feature[j].size; k++)
				printf(",%d", cascade->stage_classifier[i].feature[j].nz[k]);
			if (j < cascade->stage_classifier[i].count - 1)
				printf("]},");
			else
				printf("]}");
		}
		printf("],\"alpha\":[%le,%le", cascade->stage_classifier[i].alpha[0], cascade->stage_classifier[i].alpha[1]);
		for (j = 1; j < cascade->stage_classifier[i].count; j++)
			printf(",%le,%le", cascade->stage_classifier[i].alpha[j * 2], cascade->stage_classifier[i].alpha[j * 2 + 1]);
		if (i < cascade->count - 1)
			printf("]},");
		else
			printf("]}");
	}
	printf("]};\n");
}