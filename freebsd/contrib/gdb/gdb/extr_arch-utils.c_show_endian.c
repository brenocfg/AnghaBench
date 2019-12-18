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
 scalar_t__ BFD_ENDIAN_BIG ; 
 scalar_t__ TARGET_BYTE_ORDER ; 
 int /*<<< orphan*/  printf_unfiltered (char*,char*) ; 
 scalar_t__ target_byte_order_auto ; 

__attribute__((used)) static void
show_endian (char *args, int from_tty)
{
  if (target_byte_order_auto)
    printf_unfiltered ("The target endianness is set automatically (currently %s endian)\n",
		       (TARGET_BYTE_ORDER == BFD_ENDIAN_BIG ? "big" : "little"));
  else
    printf_unfiltered ("The target is assumed to be %s endian\n",
		       (TARGET_BYTE_ORDER == BFD_ENDIAN_BIG ? "big" : "little"));
}