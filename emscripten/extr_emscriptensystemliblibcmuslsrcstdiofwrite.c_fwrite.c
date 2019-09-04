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
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int /*<<< orphan*/  FLOCK (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  FUNLOCK (int /*<<< orphan*/ *) ; 
 size_t __fwritex (void const*,size_t,int /*<<< orphan*/ *) ; 

size_t fwrite(const void *restrict src, size_t size, size_t nmemb, FILE *restrict f)
{
	size_t k, l = size*nmemb;
	if (!size) nmemb = 0;
	FLOCK(f);
	k = __fwritex(src, l, f);
	FUNLOCK(f);
	return k==l ? nmemb : k/size;
}