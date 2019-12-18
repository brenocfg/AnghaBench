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
struct cmd_list_element {int dummy; } ;
struct charset {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  check_valid_host_charset (struct charset*) ; 
 int /*<<< orphan*/  host_charset_name ; 
 struct charset* lookup_charset_or_error (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_host_and_target_charsets (struct charset*,struct charset*) ; 
 int /*<<< orphan*/  target_charset_name ; 

__attribute__((used)) static void
set_charset_sfunc (char *charset, int from_tty, struct cmd_list_element *c)
{
  struct charset *cs = lookup_charset_or_error (host_charset_name);
  check_valid_host_charset (cs);
  /* CAREFUL: set the target charset here as well. */
  target_charset_name = host_charset_name;
  set_host_and_target_charsets (cs, cs);
}