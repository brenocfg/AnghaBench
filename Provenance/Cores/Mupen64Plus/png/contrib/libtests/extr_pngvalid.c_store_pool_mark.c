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
typedef  int /*<<< orphan*/  png_bytep ;

/* Variables and functions */
 int /*<<< orphan*/  make_four_random_bytes (int*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
store_pool_mark(png_bytep mark)
{
   static png_uint_32 store_seed[2] = { 0x12345678, 1};

   make_four_random_bytes(store_seed, mark);
}