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
typedef  int UCHAR ;

/* Variables and functions */
 int /*<<< orphan*/  Free (char*) ; 
 int /*<<< orphan*/  StrCpy (char*,int,char*) ; 
 char* ZeroMalloc (int) ; 
 int /*<<< orphan*/  sprintf (char*,char*,int) ; 

void BinToStr(char *str, UINT str_size, void *data, UINT data_size)
{
	char *tmp;
	UCHAR *buf = (UCHAR *)data;
	UINT size;
	UINT i;
	// Validate arguments
	if (str == NULL || data == NULL)
	{
		if (str != NULL)
		{
			str[0] = 0;
		}
		return;
	}

	// Calculation of size
	size = data_size * 2 + 1;
	// Memory allocation
	tmp = ZeroMalloc(size);
	// Conversion
	for (i = 0;i < data_size;i++)
	{
		sprintf(&tmp[i * 2], "%02X", buf[i]);
	}
	// Copy
	StrCpy(str, str_size, tmp);
	// Memory release
	Free(tmp);
}