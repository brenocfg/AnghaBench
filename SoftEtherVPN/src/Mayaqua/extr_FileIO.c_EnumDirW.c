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
typedef  int /*<<< orphan*/  DIRLIST ;

/* Variables and functions */
 int /*<<< orphan*/ * EnumDirExW (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

DIRLIST *EnumDirW(wchar_t *dirname)
{
	return EnumDirExW(dirname, NULL);
}