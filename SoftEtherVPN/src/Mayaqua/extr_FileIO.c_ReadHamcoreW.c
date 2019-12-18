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
typedef  int /*<<< orphan*/  wchar_t ;
typedef  int /*<<< orphan*/  BUF ;

/* Variables and functions */
 char* CopyUniToStr (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  Free (char*) ; 
 int /*<<< orphan*/ * ReadHamcore (char*) ; 

BUF *ReadHamcoreW(wchar_t *filename)
{
	char *filename_a = CopyUniToStr(filename);
	BUF *ret;

	ret = ReadHamcore(filename_a);

	Free(filename_a);

	return ret;
}