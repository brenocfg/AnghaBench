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
typedef  int /*<<< orphan*/  ENTRY ;
typedef  int /*<<< orphan*/  ACTION ;

/* Variables and functions */
 int /*<<< orphan*/  __hsearch_r (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ **,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  htab ; 

ENTRY *hsearch(ENTRY item, ACTION action)
{
	ENTRY *e;

	__hsearch_r(item, action, &e, &htab);
	return e;
}