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
typedef  char uint8_t ;

/* Variables and functions */

__attribute__((used)) static uint8_t hex_to_nybble(char hex)
{
   if (hex >= '0' && hex <= '9')
      return hex - '0';
   if (hex >= 'A' && hex <= 'F')
      return hex - 'A' + 10;
   if (hex >= 'a' && hex <= 'f')
      return hex - 'a' + 10;
   return 0;   /* Illegal character (not hex) */
}