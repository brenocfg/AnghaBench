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

/* Variables and functions */
 int /*<<< orphan*/  add_alias_cmd (char*,char*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  add_language (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  add_prefix_cmd (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 struct cmd_list_element* add_set_cmd (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,char*,int /*<<< orphan*/ *) ; 
 struct cmd_list_element* add_show_from_set (struct cmd_list_element*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  auto_language_defn ; 
 void* case_sensitive ; 
 int /*<<< orphan*/  class_support ; 
 void* language ; 
 int /*<<< orphan*/  language_auto ; 
 int /*<<< orphan*/  local_language_defn ; 
 int /*<<< orphan*/  no_class ; 
 void* range ; 
 void* savestring (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_case_command ; 
 int /*<<< orphan*/  set_check ; 
 int /*<<< orphan*/  set_cmd_cfunc (struct cmd_list_element*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_language (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_language_command ; 
 int /*<<< orphan*/  set_range_command ; 
 int /*<<< orphan*/  set_type_command ; 
 int /*<<< orphan*/  setchecklist ; 
 int /*<<< orphan*/  setlist ; 
 int /*<<< orphan*/  show_case_command ; 
 int /*<<< orphan*/  show_check ; 
 int /*<<< orphan*/  show_language_command ; 
 int /*<<< orphan*/  show_range_command ; 
 int /*<<< orphan*/  show_type_command ; 
 int /*<<< orphan*/  showchecklist ; 
 int /*<<< orphan*/  showlist ; 
 int /*<<< orphan*/  strlen (char*) ; 
 void* type ; 
 int /*<<< orphan*/  unknown_language_defn ; 
 int /*<<< orphan*/  var_string_noescape ; 

void
_initialize_language (void)
{
  struct cmd_list_element *set, *show;

  /* GDB commands for language specific stuff */

  set = add_set_cmd ("language", class_support, var_string_noescape,
		     (char *) &language,
		     "Set the current source language.",
		     &setlist);
  show = add_show_from_set (set, &showlist);
  set_cmd_cfunc (set, set_language_command);
  set_cmd_cfunc (show, show_language_command);

  add_prefix_cmd ("check", no_class, set_check,
		  "Set the status of the type/range checker.",
		  &setchecklist, "set check ", 0, &setlist);
  add_alias_cmd ("c", "check", no_class, 1, &setlist);
  add_alias_cmd ("ch", "check", no_class, 1, &setlist);

  add_prefix_cmd ("check", no_class, show_check,
		  "Show the status of the type/range checker.",
		  &showchecklist, "show check ", 0, &showlist);
  add_alias_cmd ("c", "check", no_class, 1, &showlist);
  add_alias_cmd ("ch", "check", no_class, 1, &showlist);

  set = add_set_cmd ("type", class_support, var_string_noescape,
		     (char *) &type,
		     "Set type checking.  (on/warn/off/auto)",
		     &setchecklist);
  show = add_show_from_set (set, &showchecklist);
  set_cmd_cfunc (set, set_type_command);
  set_cmd_cfunc (show, show_type_command);

  set = add_set_cmd ("range", class_support, var_string_noescape,
		     (char *) &range,
		     "Set range checking.  (on/warn/off/auto)",
		     &setchecklist);
  show = add_show_from_set (set, &showchecklist);
  set_cmd_cfunc (set, set_range_command);
  set_cmd_cfunc (show, show_range_command);

  set = add_set_cmd ("case-sensitive", class_support, var_string_noescape,
                     (char *) &case_sensitive,
                     "Set case sensitivity in name search.  (on/off/auto)\n\
For Fortran the default is off; for other languages the default is on.",
                     &setlist);
  show = add_show_from_set (set, &showlist);
  set_cmd_cfunc (set, set_case_command);
  set_cmd_cfunc (show, show_case_command);

  add_language (&unknown_language_defn);
  add_language (&local_language_defn);
  add_language (&auto_language_defn);

  language = savestring ("auto", strlen ("auto"));
  type = savestring ("auto", strlen ("auto"));
  range = savestring ("auto", strlen ("auto"));
  case_sensitive = savestring ("auto",strlen ("auto"));

  /* Have the above take effect */
  set_language (language_auto);
}