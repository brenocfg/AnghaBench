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
typedef  int /*<<< orphan*/  LIST ;

/* Variables and functions */
 int /*<<< orphan*/ * CompareInt ; 
 int /*<<< orphan*/ * NewList (int /*<<< orphan*/ *) ; 

LIST *NewIntList(bool sorted)
{
	LIST *o = NewList(sorted ? CompareInt : NULL);

	return o;
}