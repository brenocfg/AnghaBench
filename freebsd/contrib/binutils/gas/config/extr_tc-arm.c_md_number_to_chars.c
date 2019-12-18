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
typedef  int /*<<< orphan*/  valueT ;

/* Variables and functions */
 int /*<<< orphan*/  number_to_chars_bigendian (char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  number_to_chars_littleendian (char*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ target_big_endian ; 

void
md_number_to_chars (char * buf, valueT val, int n)
{
  if (target_big_endian)
    number_to_chars_bigendian (buf, val, n);
  else
    number_to_chars_littleendian (buf, val, n);
}