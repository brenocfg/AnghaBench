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
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int int32_t ;

/* Variables and functions */
 int /*<<< orphan*/ * alloc_zeroed (int,int) ; 

__attribute__((used)) static void init_cachealigned_buffer(int32_t min_size, uint8_t **out_buf_ptr, int32_t *actual_size)
{
   *actual_size = (min_size + 0x3f) & ~0x3f;

   *out_buf_ptr = alloc_zeroed(64, *actual_size);
}