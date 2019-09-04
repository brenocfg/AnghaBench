#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  Error; } ;
typedef  TYPE_1__ SECURE ;

/* Variables and functions */
 int DeleteSecObjectByName (TYPE_1__*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SEC_DATA ; 
 int /*<<< orphan*/  SEC_ERROR_BAD_PARAMETER ; 

bool DeleteSecData(SECURE *sec, char *name)
{
	// Validate arguments
	if (sec == NULL)
	{
		return false;
	}
	if (name == NULL)
	{
		sec->Error = SEC_ERROR_BAD_PARAMETER;
		return false;
	}

	return DeleteSecObjectByName(sec, name, SEC_DATA);
}