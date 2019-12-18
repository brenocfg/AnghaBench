#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ UINT ;
struct TYPE_3__ {scalar_t__ Id; } ;
typedef  TYPE_1__ SECURE_DEVICE ;

/* Variables and functions */
 TYPE_1__* LIST_DATA (int /*<<< orphan*/ ,scalar_t__) ; 
 scalar_t__ LIST_NUM (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SecureDeviceList ; 

bool CheckSecureDeviceId(UINT id)
{
	UINT i;

	for (i = 0;i < LIST_NUM(SecureDeviceList);i++)
	{
		SECURE_DEVICE *dev = LIST_DATA(SecureDeviceList, i);

		if (dev->Id == id)
		{
			return true;
		}
	}

	return false;
}