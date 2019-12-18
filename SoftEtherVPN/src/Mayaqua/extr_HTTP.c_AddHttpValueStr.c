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
typedef  int UINT ;
typedef  int /*<<< orphan*/  HTTP_VALUE ;
typedef  int /*<<< orphan*/  HTTP_HEADER ;

/* Variables and functions */
 int /*<<< orphan*/  AddHttpValue (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  Copy (char*,char*,int) ; 
 int /*<<< orphan*/  EnSafeHttpHeaderValueStr (char*,char) ; 
 int /*<<< orphan*/  Free (char*) ; 
 int INFINITE ; 
 scalar_t__ IsEmptyStr (char*) ; 
 char* Malloc (int) ; 
 int /*<<< orphan*/ * NewHttpValue (char*,char*) ; 
 int SearchStr (char*,char*,int /*<<< orphan*/ ) ; 
 int StrLen (char*) ; 

bool AddHttpValueStr(HTTP_HEADER* header, char *string)
{
	HTTP_VALUE *value = NULL;
	UINT pos = 0;
	char *value_name = NULL;
	char *value_data = NULL;

	// Validate arguments
	if (header == NULL || IsEmptyStr(string))
	{
		return false;
	}

	// Sanitize string
	EnSafeHttpHeaderValueStr(string, ' ');

	// Get the position of the colon
	pos = SearchStr(string, ":", 0);
	if (pos == INFINITE)
	{
		// The colon does not exist
		return false;
	}

	if ((pos + 1) >= StrLen(string))
	{
		// There is no data
		return false;
	}

	// Divide into the name and the data
	value_name = Malloc(pos + 1);
	Copy(value_name, string, pos);
	value_name[pos] = 0;
	value_data = &string[pos + 1];

	value = NewHttpValue(value_name, value_data);
	if (value == NULL)
	{
		Free(value_name);
		return false;
	}

	Free(value_name);

	AddHttpValue(header, value);

	return true;
}