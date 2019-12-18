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
typedef  int ObjectType ;

/* Variables and functions */
 int /*<<< orphan*/  ERROR ; 
#define  OBJECT_AGGREGATE 130 
#define  OBJECT_FUNCTION 129 
#define  OBJECT_PROCEDURE 128 
 int /*<<< orphan*/  elog (int /*<<< orphan*/ ,char*,int) ; 

__attribute__((used)) static const char *
ObjectTypeToKeyword(ObjectType objtype)
{
	switch (objtype)
	{
		case OBJECT_FUNCTION:
		{
			return "FUNCTION";
		}

		case OBJECT_PROCEDURE:
		{
			return "PROCEDURE";
		}

		case OBJECT_AGGREGATE:
		{
			return "AGGREGATE";
		}

		default:
			elog(ERROR, "Unknown object type: %d", objtype);
			return NULL;
	}
}