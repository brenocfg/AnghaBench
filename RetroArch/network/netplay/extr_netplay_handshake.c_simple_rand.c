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
 int simple_rand_next ; 

__attribute__((used)) static int simple_rand(void)
{
   simple_rand_next = simple_rand_next * 1103515245 + 12345;
   return((unsigned)(simple_rand_next/65536) % 32768);
}