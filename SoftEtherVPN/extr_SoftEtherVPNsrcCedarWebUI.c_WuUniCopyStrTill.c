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
typedef  int wchar_t ;
typedef  int UINT ;

/* Variables and functions */
 scalar_t__ Malloc (int) ; 

__attribute__((used)) static wchar_t *WuUniCopyStrTill(wchar_t *str, wchar_t delimiter, wchar_t **ret){
	UINT num = 0, i;
	wchar_t *next = str;
	wchar_t *ptr = str;

	// Count the number of characters to copy
	while(*next)
	{
		if(*next==L'\\')
		{
			next++;
			if(*next == 0)
			{
				break;
			}
		}
		else
		{
			if(*next == delimiter)
			{
				break;
			}
		}
		next++;
		num++;
	}

	// Allocate the memory and copy the string
	*ret = (wchar_t*)Malloc((num+1)*sizeof(wchar_t));
	for(i=0;i<num;i++)
	{
		if(*ptr == L'\\')
		{
			ptr++;
		}
		(*ret)[i] = *ptr;
		ptr++;
	}
	(*ret)[num]=0;

	// Return a pointer to the next to the delimiter or the end of the string
	return *next ? next+1 : next;
}