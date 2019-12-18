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
typedef  int ShardPlacementAccessType ;

/* Variables and functions */
#define  PLACEMENT_ACCESS_DDL 130 
#define  PLACEMENT_ACCESS_DML 129 
#define  PLACEMENT_ACCESS_SELECT 128 

__attribute__((used)) static char *
PlacementAccessTypeToText(ShardPlacementAccessType accessType)
{
	switch (accessType)
	{
		case PLACEMENT_ACCESS_SELECT:
		{
			return "SELECT";
			break;
		}

		case PLACEMENT_ACCESS_DML:
		{
			return "DML";
		}

		case PLACEMENT_ACCESS_DDL:
		{
			return "DDL";
		}

		default:
		{
			return "None";
			break;
		}
	}
}