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
struct TYPE_2__ {int (* memcmp ) (void const*,void const*,size_t) ;} ;

/* Variables and functions */
 TYPE_1__* _libkernel_string_functions ; 
 int stub1 (void const*,void const*,size_t) ; 

__attribute__((visibility("hidden")))
int
memcmp(const void *s1, const void *s2, size_t n)
{
	return _libkernel_string_functions->memcmp(s1, s2, n);
}