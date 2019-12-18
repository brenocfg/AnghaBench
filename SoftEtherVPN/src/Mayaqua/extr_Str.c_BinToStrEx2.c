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
typedef  int /*<<< orphan*/  UCHAR ;

/* Variables and functions */
 int /*<<< orphan*/  Format (char*,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,char) ; 
 int /*<<< orphan*/  Free (char*) ; 
 int /*<<< orphan*/  StrCpy (char*,int,char*) ; 
 int StrLen (char*) ; 
 char* ZeroMalloc (int) ; 

void BinToStrEx2(char *str, UINT str_size, void *data, UINT data_size, char padding_char)
{
	char *tmp;
	UCHAR *buf = (UCHAR *)data;
	UINT size;
	UINT i;
	// Validate arguments
	if (str == NULL || data == NULL)
	{
		return;
	}

	// Calculation of size
	size = data_size * 3 + 1;
	// Memory allocation
	tmp = ZeroMalloc(size);
	// Conversion
	for (i = 0;i < data_size;i++)
	{
		Format(&tmp[i * 3], 0, "%02X%c", buf[i], padding_char);
	}
	if (StrLen(tmp) >= 1)
	{
		if (tmp[StrLen(tmp) - 1] == padding_char)
		{
			tmp[StrLen(tmp) - 1] = 0;
		}
	}
	// Copy
	StrCpy(str, str_size, tmp);
	// Memory release
	Free(tmp);
}