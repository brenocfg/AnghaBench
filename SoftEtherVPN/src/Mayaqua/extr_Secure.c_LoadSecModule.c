#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int Initialized; TYPE_1__* Api; } ;
struct TYPE_6__ {scalar_t__ (* C_Initialize ) (int /*<<< orphan*/ *) ;} ;
typedef  TYPE_2__ SECURE ;

/* Variables and functions */
 scalar_t__ CKR_OK ; 
 int /*<<< orphan*/  FreeSecModule (TYPE_2__*) ; 
 int Win32LoadSecModule (TYPE_2__*) ; 
 scalar_t__ stub1 (int /*<<< orphan*/ *) ; 

bool LoadSecModule(SECURE *sec)
{
	bool ret = false;
	// Validate arguments
	if (sec == NULL)
	{
		return false;
	}

#ifdef	OS_WIN32
	ret = Win32LoadSecModule(sec);
#endif	// OS_WIN32

	// Initialization
	if (sec->Api->C_Initialize(NULL) != CKR_OK)
	{
		// Initialization Failed
		FreeSecModule(sec);
		return false;
	}

	sec->Initialized = true;

	return ret;
}