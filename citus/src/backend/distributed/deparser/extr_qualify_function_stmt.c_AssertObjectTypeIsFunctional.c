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
typedef  scalar_t__ ObjectType ;

/* Variables and functions */
 int /*<<< orphan*/  Assert (int) ; 
 scalar_t__ OBJECT_AGGREGATE ; 
 scalar_t__ OBJECT_FUNCTION ; 
 scalar_t__ OBJECT_PROCEDURE ; 

void
AssertObjectTypeIsFunctional(ObjectType type)
{
	Assert(type == OBJECT_AGGREGATE ||
		   type == OBJECT_FUNCTION ||
		   type == OBJECT_PROCEDURE);
}