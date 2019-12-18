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
typedef  int png_alloc_size_t ;

/* Variables and functions */

__attribute__((used)) static int
is_ICC_signature_char(png_alloc_size_t it)
{
   return it == 32 || (it >= 48 && it <= 57) || (it >= 65 && it <= 90) ||
      (it >= 97 && it <= 122);
}