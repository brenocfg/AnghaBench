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
typedef  int /*<<< orphan*/  u32 ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 size_t format_array (char*,size_t,char const*,int /*<<< orphan*/ *,unsigned int) ; 
 char* kmalloc (size_t,int /*<<< orphan*/ ) ; 

__attribute__((used)) static char *format_array_alloc(const char *fmt, u32 *array, unsigned array_size)
{
	size_t len = format_array(NULL, 0, fmt, array, array_size);
	char *ret;

	ret = kmalloc(len, GFP_KERNEL);
	if (ret == NULL)
		return NULL;

	format_array(ret, len, fmt, array, array_size);
	return ret;
}