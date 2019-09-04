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

/* Variables and functions */
 int /*<<< orphan*/  ReplaceStrEx (char*,int /*<<< orphan*/ ,char*,char*,char*,int) ; 

UINT ReplaceStri(char *dst, UINT size, char *string, char *old_keyword, char *new_keyword)
{
	return ReplaceStrEx(dst, size, string, old_keyword, new_keyword, false);
}