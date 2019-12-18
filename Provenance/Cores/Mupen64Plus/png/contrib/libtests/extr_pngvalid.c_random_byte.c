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
typedef  unsigned char png_byte ;

/* Variables and functions */
 int /*<<< orphan*/  randomize (unsigned char*,int) ; 

__attribute__((used)) static png_byte
random_byte(void)
{
   unsigned char b1[1];
   randomize(b1, sizeof b1);
   return b1[0];
}