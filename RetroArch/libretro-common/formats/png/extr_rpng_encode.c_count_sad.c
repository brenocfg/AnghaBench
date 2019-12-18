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
typedef  scalar_t__ uint8_t ;
typedef  int /*<<< orphan*/  int8_t ;

/* Variables and functions */
 scalar_t__ abs (int /*<<< orphan*/ ) ; 

__attribute__((used)) static unsigned count_sad(const uint8_t *data, size_t size)
{
   size_t i;
   unsigned cnt = 0;
   for (i = 0; i < size; i++)
   {
      if (data[i])
         cnt += abs((int8_t)data[i]);
   }
   return cnt;
}