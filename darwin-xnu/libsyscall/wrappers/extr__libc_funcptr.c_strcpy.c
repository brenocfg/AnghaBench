#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {char* (* strcpy ) (char*,char const*) ;} ;

/* Variables and functions */
 TYPE_1__* _libkernel_string_functions ; 
 char* stub1 (char*,char const*) ; 

__attribute__((visibility("hidden")))
char *
strcpy(char * restrict dst, const char * restrict src)
{
	return _libkernel_string_functions->strcpy(dst, src);
}