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
 int /*<<< orphan*/  CURRENT_LOCALE ; 
 size_t __strxfrm_l (char*,char const*,size_t,int /*<<< orphan*/ ) ; 

size_t strxfrm(char *restrict dest, const char *restrict src, size_t n)
{
	return __strxfrm_l(dest, src, n, CURRENT_LOCALE);
}