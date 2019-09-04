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

/* Variables and functions */
 int /*<<< orphan*/  free (char*) ; 
 scalar_t__ malloc (int) ; 
 int /*<<< orphan*/  str_copy (char*,char const*,int) ; 
 int str_len (char*) ; 

char *str_join(char *a, const char *b, int lenb)
{
	//连接字符串 第一个字符串被回收
	char *t;
	if (a == 0)
	{
		t = (char *) malloc(sizeof(char) * (lenb + 1));
		str_copy(t, b, lenb);
		return t;
	}
	else
	{
		int lena = str_len(a);
		t = (char *) malloc(sizeof(char) * (lena + lenb + 2));
		str_copy(t, a, lena);
		*(t + lena) = ' ';
		str_copy(t + lena + 1, b, lenb);
		free(a);
		return t;
	}
}