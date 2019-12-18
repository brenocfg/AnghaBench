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
typedef  int uint32_t ;
struct TYPE_3__ {float* posterior; int structs; int posteriors; } ;
typedef  TYPE_1__ ccv_ferns_t ;

/* Variables and functions */

float ccv_ferns_predict(ccv_ferns_t* ferns, uint32_t* fern)
{
	float votes[] = {0, 0};
	int i;
	float* post = ferns->posterior;
	for (i = 0; i < ferns->structs; i++)
	{
		votes[0] += post[fern[i] * 2];
		votes[1] += post[fern[i] * 2 + 1];
		post += ferns->posteriors * 2;
	}
	return votes[1] - votes[0];
}