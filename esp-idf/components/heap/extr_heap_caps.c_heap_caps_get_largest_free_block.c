#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint32_t ;
struct TYPE_3__ {size_t largest_free_block; } ;
typedef  TYPE_1__ multi_heap_info_t ;

/* Variables and functions */
 int /*<<< orphan*/  heap_caps_get_info (TYPE_1__*,int /*<<< orphan*/ ) ; 

size_t heap_caps_get_largest_free_block( uint32_t caps )
{
    multi_heap_info_t info;
    heap_caps_get_info(&info, caps);
    return info.largest_free_block;
}