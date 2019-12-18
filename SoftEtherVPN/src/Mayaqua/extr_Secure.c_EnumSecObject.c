#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  priv ;
typedef  int /*<<< orphan*/  objects ;
typedef  int /*<<< orphan*/  obj_class ;
typedef  int /*<<< orphan*/  label ;
typedef  int /*<<< orphan*/  get ;
typedef  int /*<<< orphan*/  dummy ;
typedef  int /*<<< orphan*/  b_true ;
typedef  int /*<<< orphan*/  a ;
typedef  scalar_t__ UINT ;
struct TYPE_9__ {int SessionCreated; int /*<<< orphan*/ * EnumCache; int /*<<< orphan*/  SessionId; TYPE_1__* Api; void* Error; } ;
struct TYPE_8__ {int Private; int /*<<< orphan*/  Name; scalar_t__ Object; scalar_t__ Type; } ;
struct TYPE_7__ {scalar_t__ (* C_FindObjectsInit ) (int /*<<< orphan*/ ,char*,int) ;scalar_t__ (* C_FindObjects ) (int /*<<< orphan*/ ,scalar_t__*,int,scalar_t__*) ;scalar_t__ (* C_GetAttributeValue ) (int /*<<< orphan*/ ,scalar_t__,char*,int) ;int /*<<< orphan*/  (* C_FindObjectsFinal ) (int /*<<< orphan*/ ) ;} ;
typedef  TYPE_2__ SEC_OBJ ;
typedef  TYPE_3__ SECURE ;
typedef  int /*<<< orphan*/  LIST ;
typedef  int CK_BBOOL ;
typedef  char CK_ATTRIBUTE ;

/* Variables and functions */
 int /*<<< orphan*/  Add (int /*<<< orphan*/ *,TYPE_2__*) ; 
 int /*<<< orphan*/  CKA_CLASS ; 
 int /*<<< orphan*/  CKA_LABEL ; 
 int /*<<< orphan*/  CKA_PRIVATE ; 
 int /*<<< orphan*/  CKA_TOKEN ; 
#define  CKO_CERTIFICATE 131 
#define  CKO_DATA 130 
#define  CKO_PRIVATE_KEY 129 
#define  CKO_PUBLIC_KEY 128 
 scalar_t__ CKR_OK ; 
 int /*<<< orphan*/ * CloneEnumSecObject (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  CopyStr (char*) ; 
 int /*<<< orphan*/  EnSafeStr (char*,char) ; 
 scalar_t__ INFINITE ; 
 int MAX_OBJ ; 
 int MAX_SIZE ; 
 int /*<<< orphan*/ * NewListFast (int /*<<< orphan*/ *) ; 
 scalar_t__ SEC_DATA ; 
 void* SEC_ERROR_HARDWARE_ERROR ; 
 void* SEC_ERROR_NO_SESSION ; 
 scalar_t__ SEC_K ; 
 scalar_t__ SEC_P ; 
 scalar_t__ SEC_X ; 
 int /*<<< orphan*/  TruncateCharFromStr (char*,char) ; 
 int /*<<< orphan*/  Zero (char*,int) ; 
 TYPE_2__* ZeroMalloc (int) ; 
 scalar_t__ stub1 (int /*<<< orphan*/ ,char*,int) ; 
 scalar_t__ stub2 (int /*<<< orphan*/ ,scalar_t__*,int,scalar_t__*) ; 
 int /*<<< orphan*/  stub3 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub4 (int /*<<< orphan*/ ) ; 
 scalar_t__ stub5 (int /*<<< orphan*/ ,scalar_t__,char*,int) ; 

LIST *EnumSecObject(SECURE *sec)
{
	CK_BBOOL b_true = true, b_false = false;
	UINT objects[MAX_OBJ];
	UINT i;
	UINT ret;
	LIST *o;
	CK_ATTRIBUTE dummy[1];
	CK_ATTRIBUTE a[] =
	{
		{CKA_TOKEN,		&b_true,		sizeof(b_true)},
	};
	UINT num_objects = MAX_OBJ;
	// Validate arguments
	if (sec == NULL)
	{
		return NULL;
	}
	if (sec->SessionCreated == false)
	{
		sec->Error = SEC_ERROR_NO_SESSION;
		return NULL;
	}

	Zero(dummy, sizeof(dummy));

	// If there is a cache, return it
	if (sec->EnumCache != NULL)
	{
		return CloneEnumSecObject(sec->EnumCache);
	}

	// Enumerate
//	if (sec->Dev->Id != 2 && sec->Dev->Id != 14)
//	{
		// Normal tokens
		ret = sec->Api->C_FindObjectsInit(sec->SessionId, a, sizeof(a) / sizeof(a[0]));
//	}
//	else
//	{
		// ePass and SafeSign
//		ret = sec->Api->C_FindObjectsInit(sec->SessionId, dummy, 0);
//	}

	if (ret != CKR_OK)
	{
		sec->Error = SEC_ERROR_HARDWARE_ERROR;
		return NULL;
	}
	if (sec->Api->C_FindObjects(sec->SessionId, objects, sizeof(objects) / sizeof(objects[0]), &num_objects) != CKR_OK)
	{
		sec->Api->C_FindObjectsFinal(sec->SessionId);
		sec->Error = SEC_ERROR_HARDWARE_ERROR;
		return NULL;
	}
	sec->Api->C_FindObjectsFinal(sec->SessionId);

	o = NewListFast(NULL);

	for (i = 0;i < num_objects;i++)
	{
		char label[MAX_SIZE];
		UINT obj_class = 0;
		bool priv = false;
		CK_ATTRIBUTE get[] =
		{
			{CKA_LABEL, label, sizeof(label) - 1},
			{CKA_CLASS, &obj_class, sizeof(obj_class)},
			{CKA_PRIVATE, &priv, sizeof(priv)},
		};

		Zero(label, sizeof(label));

		if (sec->Api->C_GetAttributeValue(sec->SessionId, objects[i],
			get, sizeof(get) / sizeof(get[0])) == CKR_OK)
		{
			UINT type = INFINITE;

			switch (obj_class)
			{
			case CKO_DATA:
				// Data
				type = SEC_DATA;
				break;

			case CKO_CERTIFICATE:
				// Certificate
				type = SEC_X;
				break;

			case CKO_PUBLIC_KEY:
				// Public key
				type = SEC_P;
				break;

			case CKO_PRIVATE_KEY:
				// Secret key
				type = SEC_K;
				break;
			}

			if (type != INFINITE)
			{
				SEC_OBJ *obj = ZeroMalloc(sizeof(SEC_OBJ));

				obj->Type = type;
				obj->Object = objects[i];
				obj->Private = (priv == false) ? false : true;
				EnSafeStr(label, '?');
				TruncateCharFromStr(label, '?');
				obj->Name = CopyStr(label);

				Add(o, obj);
			}
		}
	}

	// Creating a cache
	sec->EnumCache = CloneEnumSecObject(o);

	return o;
}