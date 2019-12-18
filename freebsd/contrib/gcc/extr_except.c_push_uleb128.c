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
typedef  int /*<<< orphan*/  varray_type ;

/* Variables and functions */
 int /*<<< orphan*/  VARRAY_PUSH_UCHAR (int /*<<< orphan*/ ,unsigned char) ; 

__attribute__((used)) static void
push_uleb128 (varray_type *data_area, unsigned int value)
{
  do
    {
      unsigned char byte = value & 0x7f;
      value >>= 7;
      if (value)
	byte |= 0x80;
      VARRAY_PUSH_UCHAR (*data_area, byte);
    }
  while (value);
}