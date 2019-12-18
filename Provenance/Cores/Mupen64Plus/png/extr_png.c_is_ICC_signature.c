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
 scalar_t__ is_ICC_signature_char (int) ; 

__attribute__((used)) static int
is_ICC_signature(png_alloc_size_t it)
{
   return is_ICC_signature_char(it >> 24) /* checks all the top bits */ &&
      is_ICC_signature_char((it >> 16) & 0xff) &&
      is_ICC_signature_char((it >> 8) & 0xff) &&
      is_ICC_signature_char(it & 0xff);
}