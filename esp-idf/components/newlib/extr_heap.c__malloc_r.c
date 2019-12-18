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
struct _reent {int dummy; } ;

/* Variables and functions */
 void* heap_caps_malloc_default (size_t) ; 

void* _malloc_r(struct _reent *r, size_t size)
{
    return heap_caps_malloc_default(size);
}