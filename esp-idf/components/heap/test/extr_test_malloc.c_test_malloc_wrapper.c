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
 void* g_test_malloc_ptr (size_t) ; 
 void* stub1 (size_t) ; 

void* test_malloc_wrapper(size_t size)
{
    return (*g_test_malloc_ptr)(size);
}