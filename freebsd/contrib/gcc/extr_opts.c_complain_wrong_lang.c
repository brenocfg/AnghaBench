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
struct cl_option {unsigned int flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  free (char*) ; 
 int /*<<< orphan*/  warning (int /*<<< orphan*/ ,char*,char const*,char*,char*) ; 
 char* write_langs (unsigned int) ; 

__attribute__((used)) static void
complain_wrong_lang (const char *text, const struct cl_option *option,
		     unsigned int lang_mask)
{
  char *ok_langs, *bad_lang;

  ok_langs = write_langs (option->flags);
  bad_lang = write_langs (lang_mask);

  /* Eventually this should become a hard error IMO.  */
  warning (0, "command line option \"%s\" is valid for %s but not for %s",
	   text, ok_langs, bad_lang);

  free (ok_langs);
  free (bad_lang);
}