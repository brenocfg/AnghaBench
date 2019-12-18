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
 int eh_addr_size ; 

__attribute__((used)) static int
size_of_encoded_value (int encoding)
{
  switch (encoding & 0x7)
    {
    default:	/* ??? */
    case 0:	return eh_addr_size;
    case 2:	return 2;
    case 3:	return 4;
    case 4:	return 8;
    }
}