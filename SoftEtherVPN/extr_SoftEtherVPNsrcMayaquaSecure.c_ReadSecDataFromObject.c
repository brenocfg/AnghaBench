#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  get ;
typedef  int /*<<< orphan*/  buf ;
typedef  scalar_t__ UINT ;
typedef  int /*<<< orphan*/  UCHAR ;
struct TYPE_11__ {int member_2; scalar_t__ ulValueLen; int /*<<< orphan*/ * member_1; int /*<<< orphan*/  member_0; } ;
struct TYPE_10__ {int SessionCreated; int LoginFlag; void* Error; int /*<<< orphan*/  SessionId; TYPE_1__* Api; } ;
struct TYPE_9__ {scalar_t__ Type; int /*<<< orphan*/  Object; scalar_t__ Private; } ;
struct TYPE_8__ {scalar_t__ (* C_GetAttributeValue ) (int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_4__*,int) ;} ;
typedef  TYPE_2__ SEC_OBJ ;
typedef  TYPE_3__ SECURE ;
typedef  TYPE_4__ CK_ATTRIBUTE ;

/* Variables and functions */
 int /*<<< orphan*/  CKA_VALUE ; 
 scalar_t__ CKR_OK ; 
 int /*<<< orphan*/  Copy (void*,int /*<<< orphan*/ *,scalar_t__) ; 
 int MAX_SEC_DATA_SIZE ; 
 scalar_t__ SEC_DATA ; 
 void* SEC_ERROR_BAD_PARAMETER ; 
 void* SEC_ERROR_DATA_TOO_BIG ; 
 void* SEC_ERROR_HARDWARE_ERROR ; 
 void* SEC_ERROR_NOT_LOGIN ; 
 void* SEC_ERROR_NO_SESSION ; 
 scalar_t__ stub1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_4__*,int) ; 

int ReadSecDataFromObject(SECURE *sec, SEC_OBJ *obj, void *data, UINT size)
{
	UCHAR buf[MAX_SEC_DATA_SIZE];
	UINT i;
	CK_ATTRIBUTE get[] =
	{
		{CKA_VALUE,	 buf,	sizeof(buf)},
	};
	// Validate arguments
	if (sec == NULL)
	{
		return 0;
	}
	if (obj == NULL || data == NULL || size == 0)
	{
		sec->Error = SEC_ERROR_BAD_PARAMETER;
		return 0;
	}
	if (obj->Type != SEC_DATA)
	{
		sec->Error = SEC_ERROR_BAD_PARAMETER;
		return false;
	}
	if (sec->SessionCreated == false)
	{
		sec->Error = SEC_ERROR_NO_SESSION;
		return 0;
	}
	if (sec->LoginFlag == false && obj->Private)
	{
		sec->Error = SEC_ERROR_NOT_LOGIN;
		return 0;
	}

	// Acquisition
	if (sec->Api->C_GetAttributeValue(
		sec->SessionId, obj->Object, get, sizeof(get) / sizeof(get[0])) != CKR_OK)
	{
		sec->Error = SEC_ERROR_HARDWARE_ERROR;
		return 0;
	}

	// Return the result
	i = get[0].ulValueLen;
	if (i > MAX_SEC_DATA_SIZE || i > size)
	{
		// Data is too large
		sec->Error = SEC_ERROR_DATA_TOO_BIG;
		return 0;
	}

	// Memory copy
	Copy(data, buf, i);

	return i;
}