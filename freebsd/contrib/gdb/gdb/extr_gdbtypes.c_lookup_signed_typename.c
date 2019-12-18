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
struct type {int dummy; } ;
struct block {int dummy; } ;

/* Variables and functions */
 char* alloca (scalar_t__) ; 
 struct type* lookup_typename (char*,struct block*,int) ; 
 int /*<<< orphan*/  strcpy (char*,char*) ; 
 scalar_t__ strlen (char*) ; 

struct type *
lookup_signed_typename (char *name)
{
  struct type *t;
  char *uns = alloca (strlen (name) + 8);

  strcpy (uns, "signed ");
  strcpy (uns + 7, name);
  t = lookup_typename (uns, (struct block *) NULL, 1);
  /* If we don't find "signed FOO" just try again with plain "FOO". */
  if (t != NULL)
    return t;
  return lookup_typename (name, (struct block *) NULL, 0);
}