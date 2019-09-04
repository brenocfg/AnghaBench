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
 int FALSE ; 
 int TRUE ; 

__attribute__((used)) static bool is_ASCII_name(const char *hostname)
{
  const unsigned char *ch = (const unsigned char *)hostname;

  while(*ch) {
    if(*ch++ & 0x80)
      return FALSE;
  }
  return TRUE;
}