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
typedef  int png_uint_32 ;

/* Variables and functions */
 int /*<<< orphan*/  make_random_bytes (int*,void*,size_t) ; 

__attribute__((used)) static void
clear(void *pv, size_t size)
{
   static png_uint_32 clear_seed[2] = { 0x12345678, 0x9abcdef0 };
   make_random_bytes(clear_seed, pv, size);
}