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
 scalar_t__ strcmp (char*,char*) ; 

__attribute__((used)) static char *
section_translate (char *n)
{
  if (strcmp (n, ".text") == 0)
    return "P";
  if (strcmp (n, ".data") == 0)
    return "D";
  if (strcmp (n, ".bss") == 0)
    return "B";
  return n;
}