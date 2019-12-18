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
 int /*<<< orphan*/  local_hex_format_prefix () ; 
 char* local_hex_format_specifier () ; 
 char* local_hex_format_suffix () ; 
 int /*<<< orphan*/  strcat (char*,char*) ; 
 int /*<<< orphan*/  strcpy (char*,int /*<<< orphan*/ ) ; 

char *
local_hex_format_custom (char *pre)
{
  static char form[50];

  strcpy (form, local_hex_format_prefix ());
  strcat (form, "%");
  strcat (form, pre);
  strcat (form, local_hex_format_specifier ());
  strcat (form, local_hex_format_suffix ());
  return form;
}