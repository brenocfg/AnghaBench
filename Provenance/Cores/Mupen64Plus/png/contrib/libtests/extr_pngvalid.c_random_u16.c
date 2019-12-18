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
typedef  int /*<<< orphan*/  png_uint_16 ;

/* Variables and functions */
 int /*<<< orphan*/  png_get_uint_16 (unsigned char*) ; 
 int /*<<< orphan*/  randomize (unsigned char*,int) ; 

__attribute__((used)) static png_uint_16
random_u16(void)
{
   unsigned char b2[2];
   randomize(b2, sizeof b2);
   return png_get_uint_16(b2);
}