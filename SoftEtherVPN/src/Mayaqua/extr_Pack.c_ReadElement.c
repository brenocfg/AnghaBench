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
typedef  int /*<<< orphan*/  name ;
typedef  int /*<<< orphan*/  VALUE ;
typedef  int UINT ;
typedef  int /*<<< orphan*/  ELEMENT ;
typedef  int /*<<< orphan*/  BUF ;

/* Variables and functions */
 int /*<<< orphan*/  Free (int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  MAX_ELEMENT_NAME_LEN ; 
 int MAX_VALUE_NUM ; 
 scalar_t__ Malloc (int) ; 
 int /*<<< orphan*/ * NewElement (char*,int,int,int /*<<< orphan*/ **) ; 
 int ReadBufInt (int /*<<< orphan*/ *) ; 
 int ReadBufStr (int /*<<< orphan*/ *,char*,int) ; 
 int /*<<< orphan*/ * ReadValue (int /*<<< orphan*/ *,int) ; 

ELEMENT *ReadElement(BUF *b)
{
	UINT i;
	char name[MAX_ELEMENT_NAME_LEN + 1];
	UINT type, num_value;
	VALUE **values;
	ELEMENT *e;
	// Validate arguments
	if (b == NULL)
	{
		return NULL;
	}

	// Name
	if (ReadBufStr(b, name, sizeof(name)) == false)
	{
		return NULL;
	}

	// Type of item
	type = ReadBufInt(b);

	// Number of items
	num_value = ReadBufInt(b);
	if (num_value > MAX_VALUE_NUM)
	{
		// Number exceeds
		return NULL;
	}

	// VALUE
	values = (VALUE **)Malloc(sizeof(VALUE *) * num_value);
	for (i = 0;i < num_value;i++)
	{
		values[i] = ReadValue(b, type);
	}

	// Create a ELEMENT
	e = NewElement(name, type, num_value, values);

	Free(values);

	return e;
}