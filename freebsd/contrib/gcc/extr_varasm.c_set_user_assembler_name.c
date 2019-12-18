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
typedef  int /*<<< orphan*/  tree ;

/* Variables and functions */
 int /*<<< orphan*/  NULL_RTX ; 
 int /*<<< orphan*/  SET_DECL_RTL (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 char* alloca (scalar_t__) ; 
 int /*<<< orphan*/  change_decl_assembler_name (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  get_identifier (char*) ; 
 int /*<<< orphan*/  strcpy (char*,char const*) ; 
 scalar_t__ strlen (char const*) ; 

void
set_user_assembler_name (tree decl, const char *name)
{
  char *starred = alloca (strlen (name) + 2);
  starred[0] = '*';
  strcpy (starred + 1, name);
  change_decl_assembler_name (decl, get_identifier (starred));
  SET_DECL_RTL (decl, NULL_RTX);
}