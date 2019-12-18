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
struct tree_opt_pass {int static_pass_number; int /*<<< orphan*/  letter; int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int PROP_trees ; 
 int TDF_IPA ; 
 int TDF_RTL ; 
 int TDF_TREE ; 
 char* concat (char const*,int /*<<< orphan*/ ,char*,...) ; 
 int dump_register (char*,char*,char*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sprintf (char*,char*,int) ; 

__attribute__((used)) static void
register_one_dump_file (struct tree_opt_pass *pass, bool ipa, int properties)
{
  char *dot_name, *flag_name, *glob_name;
  const char *prefix;
  char num[10];
  int flags;

  /* See below in next_pass_1.  */
  num[0] = '\0';
  if (pass->static_pass_number != -1)
    sprintf (num, "%d", ((int) pass->static_pass_number < 0
			 ? 1 : pass->static_pass_number));

  dot_name = concat (".", pass->name, num, NULL);
  if (ipa)
    prefix = "ipa-", flags = TDF_IPA;
  else if (properties & PROP_trees)
    prefix = "tree-", flags = TDF_TREE;
  else
    prefix = "rtl-", flags = TDF_RTL;

  flag_name = concat (prefix, pass->name, num, NULL);
  glob_name = concat (prefix, pass->name, NULL);
  pass->static_pass_number = dump_register (dot_name, flag_name, glob_name,
                                            flags, pass->letter);
}