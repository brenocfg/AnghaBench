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
struct partial_symtab {int dummy; } ;
struct objfile {int dummy; } ;
typedef  enum language { ____Placeholder_language } language ;

/* Variables and functions */
 int language_unknown ; 
 int /*<<< orphan*/ * lookup_minimal_symbol (char*,char const*,struct objfile*) ; 

enum language
ada_update_initial_language (enum language lang,
			     struct partial_symtab *main_pst)
{
  if (lookup_minimal_symbol ("adainit", (const char *) NULL,
			     (struct objfile *) NULL) != NULL)
    /*    return language_ada; */
    /* FIXME: language_ada should be defined in defs.h */
    return language_unknown;

  return lang;
}