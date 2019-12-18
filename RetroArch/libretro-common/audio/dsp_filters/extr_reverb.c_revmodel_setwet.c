#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct revmodel {float wet; } ;

/* Variables and functions */
 int /*<<< orphan*/  revmodel_update (struct revmodel*) ; 
 float scalewet ; 

__attribute__((used)) static void revmodel_setwet(struct revmodel *rev, float value)
{
   rev->wet = value * scalewet;
   revmodel_update(rev);
}