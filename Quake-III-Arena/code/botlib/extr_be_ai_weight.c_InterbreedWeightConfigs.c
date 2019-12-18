#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int numweights; TYPE_1__* weights; } ;
typedef  TYPE_2__ weightconfig_t ;
struct TYPE_9__ {int /*<<< orphan*/  (* Print ) (int /*<<< orphan*/ ,char*) ;} ;
struct TYPE_7__ {int /*<<< orphan*/  firstseperator; } ;

/* Variables and functions */
 int /*<<< orphan*/  InterbreedFuzzySeperator_r (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PRT_ERROR ; 
 TYPE_3__ botimport ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,char*) ; 

void InterbreedWeightConfigs(weightconfig_t *config1, weightconfig_t *config2,
								weightconfig_t *configout)
{
	int i;

	if (config1->numweights != config2->numweights ||
		config1->numweights != configout->numweights)
	{
		botimport.Print(PRT_ERROR, "cannot interbreed weight configs, unequal numweights\n");
		return;
	} //end if
	for (i = 0; i < config1->numweights; i++)
	{
		InterbreedFuzzySeperator_r(config1->weights[i].firstseperator,
									config2->weights[i].firstseperator,
									configout->weights[i].firstseperator);
	} //end for
}