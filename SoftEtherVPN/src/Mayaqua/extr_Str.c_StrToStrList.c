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
typedef  scalar_t__ UINT ;
typedef  int /*<<< orphan*/  LIST ;

/* Variables and functions */
 int /*<<< orphan*/  Add (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/ * NewListFast (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  StrCpy (char*,scalar_t__,char*) ; 
 scalar_t__ StrLen (char*) ; 
 scalar_t__ StrSize (char*) ; 
 char* ZeroMalloc (scalar_t__) ; 

LIST *StrToStrList(char *str, UINT size)
{
	LIST *o;
	char *tmp;
	UINT tmp_size;
	UINT i;
	// Validate arguments
	if (str == NULL)
	{
		return NULL;
	}

	o = NewListFast(NULL);

	i = 0;
	while (true)
	{
		if (i >= size)
		{
			break;
		}
		if (*str == 0)
		{
			break;
		}

		tmp_size = StrSize(str);
		tmp = ZeroMalloc(tmp_size);
		StrCpy(tmp, tmp_size, str);
		Add(o, tmp);
		str += StrLen(str) + 1;
		i++;
	}

	return o;
}