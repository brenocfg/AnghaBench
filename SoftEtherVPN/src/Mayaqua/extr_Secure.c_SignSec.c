#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int UINT ;
struct TYPE_5__ {int /*<<< orphan*/  Error; } ;
typedef  int /*<<< orphan*/  SEC_OBJ ;
typedef  TYPE_1__ SECURE ;

/* Variables and functions */
 int /*<<< orphan*/ * FindSecObject (TYPE_1__*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FreeSecObject (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SEC_ERROR_BAD_PARAMETER ; 
 int /*<<< orphan*/  SEC_K ; 
 int SignSecByObject (TYPE_1__*,int /*<<< orphan*/ *,void*,void*,int) ; 

bool SignSec(SECURE *sec, char *name, void *dst, void *src, UINT size)
{
	SEC_OBJ *obj;
	UINT ret;
	// Validate arguments
	if (sec == NULL)
	{
		return false;
	}
	if (name == NULL || dst == NULL || src == NULL)
	{
		sec->Error = SEC_ERROR_BAD_PARAMETER;
		return false;
	}

	obj = FindSecObject(sec, name, SEC_K);
	if (obj == NULL)
	{
		return false;
	}

	ret = SignSecByObject(sec, obj, dst, src, size);

	FreeSecObject(obj);

	return ret;
}