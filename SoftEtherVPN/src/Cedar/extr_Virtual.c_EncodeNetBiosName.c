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
typedef  char UCHAR ;

/* Variables and functions */
 char* CharToNetBiosStr (char) ; 
 int /*<<< orphan*/  Copy (char*,char*,int) ; 
 int StrLen (char*) ; 

void EncodeNetBiosName(UCHAR *dst, char *src)
{
	char tmp[17];
	UINT i;
	UINT copy_len;
	UINT wp;
	// Validate arguments
	if (dst == NULL || src == NULL)
	{
		return;
	}

	for (i = 0;i < 16;i++)
	{
		tmp[i] = ' ';
	}
	tmp[16] = 0;

	copy_len = StrLen(src);
	if (copy_len > 16)
	{
		copy_len = 16;
	}

	Copy(tmp, src, copy_len);

	wp = 0;

	tmp[15] = 0;

	for (i = 0;i < 16;i++)
	{
		char c = tmp[i];
		char *s = CharToNetBiosStr(c);

		dst[wp++] = s[0];
		dst[wp++] = s[1];
	}
}