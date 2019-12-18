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
struct TYPE_5__ {int numweights; TYPE_1__* weights; } ;
typedef  TYPE_2__ weightconfig_t ;
struct TYPE_4__ {int /*<<< orphan*/  firstseperator; int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int /*<<< orphan*/  ScaleFuzzySeperator_r (int /*<<< orphan*/ ,float) ; 
 int /*<<< orphan*/  strcmp (char*,int /*<<< orphan*/ ) ; 

void ScaleWeight(weightconfig_t *config, char *name, float scale)
{
	int i;

	if (scale < 0) scale = 0;
	else if (scale > 1) scale = 1;
	for (i = 0; i < config->numweights; i++)
	{
		if (!strcmp(name, config->weights[i].name))
		{
			ScaleFuzzySeperator_r(config->weights[i].firstseperator, scale);
			break;
		} //end if
	} //end for
}