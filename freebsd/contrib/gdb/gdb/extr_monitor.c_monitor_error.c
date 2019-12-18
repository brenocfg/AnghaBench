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
typedef  int /*<<< orphan*/  CORE_ADDR ;

/* Variables and functions */
 char* alloca (int) ; 
 int /*<<< orphan*/  error (char*,char*,char*,char*,char*,...) ; 
 int /*<<< orphan*/  monitor_printable_string (char*,char*,int) ; 
 char* paddr_nz (int /*<<< orphan*/ ) ; 
 int strlen (char*) ; 

__attribute__((used)) static void
monitor_error (char *function, char *message,
	       CORE_ADDR memaddr, int len, char *string, int final_char)
{
  int real_len = (len == 0 && string != (char *) 0) ? strlen (string) : len;
  char *safe_string = alloca ((real_len * 4) + 1);
  monitor_printable_string (safe_string, string, real_len);

  if (final_char)
    error ("%s (0x%s): %s: %s%c", function, paddr_nz (memaddr), message, safe_string, final_char);
  else
    error ("%s (0x%s): %s: %s", function, paddr_nz (memaddr), message, safe_string);
}