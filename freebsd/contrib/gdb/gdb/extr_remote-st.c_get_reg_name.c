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
 char* REGISTER_NAME (int) ; 
 int /*<<< orphan*/  toupper (char const) ; 

__attribute__((used)) static char *
get_reg_name (int regno)
{
  static char buf[50];
  const char *p;
  char *b;

  b = buf;

  for (p = REGISTER_NAME (regno); *p; p++)
    *b++ = toupper (*p);
  *b = '\000';

  return buf;
}