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
typedef  scalar_t__ png_uint_32 ;
typedef  int /*<<< orphan*/  png_byte ;

/* Variables and functions */
 scalar_t__ png_get_uint_32 (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  store_pool_mark (int /*<<< orphan*/ *) ; 

__attribute__((used)) static png_uint_32
random_32(void)
{

   for (;;)
   {
      png_byte mark[4];
      png_uint_32 result;

      store_pool_mark(mark);
      result = png_get_uint_32(mark);

      if (result != 0)
         return result;
   }
}