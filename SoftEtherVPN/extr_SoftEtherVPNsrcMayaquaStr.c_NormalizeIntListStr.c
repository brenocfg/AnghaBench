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
typedef  int /*<<< orphan*/  UINT ;
typedef  int /*<<< orphan*/  LIST ;

/* Variables and functions */
 int /*<<< orphan*/  IntListToStr (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  ReleaseIntList (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * StrToIntList (char*,int) ; 

void NormalizeIntListStr(char *dst, UINT dst_size, char *src, bool sorted, char *separate_str)
{
	LIST *o;

	o = StrToIntList(src, sorted);

	IntListToStr(dst, dst_size, o, separate_str);

	ReleaseIntList(o);
}