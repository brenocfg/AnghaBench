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
 int /*<<< orphan*/  hook_char_replace (char*,size_t,char,char) ; 
 size_t strlen (char*) ; 

void
run_replaces (char * string)
{
  /* Store original string size */
  size_t len = strlen (string);
  hook_char_replace (string, len, '\b', '\0');
}