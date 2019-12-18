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
typedef  int uint32_t ;

/* Variables and functions */
 int TLSP_DEL_BASE ; 

__attribute__((used)) static void del_cb(int index, void *ptr)
{
    *((uint32_t *)ptr) = (TLSP_DEL_BASE << index);   //Indicate deletion by setting task storage element to a unique value
}