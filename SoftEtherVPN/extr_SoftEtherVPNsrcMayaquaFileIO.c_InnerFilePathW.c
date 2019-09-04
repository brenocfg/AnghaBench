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
typedef  int /*<<< orphan*/  dir ;
typedef  int /*<<< orphan*/  UINT ;

/* Variables and functions */
 int /*<<< orphan*/  ConbinePathW (int*,int /*<<< orphan*/ ,int*,int*) ; 
 int /*<<< orphan*/  GetExeDirW (int*,int) ; 
 int MAX_SIZE ; 
 int /*<<< orphan*/  NormalizePathW (int*,int /*<<< orphan*/ ,int*) ; 

void InnerFilePathW(wchar_t *dst, UINT size, wchar_t *src)
{
	// Validate arguments
	if (dst == NULL || src == NULL)
	{
		return;
	}

	if (src[0] != L'@')
	{
		NormalizePathW(dst, size, src);
	}
	else
	{
		wchar_t dir[MAX_SIZE];
		GetExeDirW(dir, sizeof(dir));
		ConbinePathW(dst, size, dir, &src[1]);
	}
}