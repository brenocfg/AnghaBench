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
 struct type* lookup_typename (char*,struct block*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strcpy (char*,char*) ; 
 scalar_t__ strlen (char*) ; 

struct type *
lookup_unsigned_typename (char *name)
{
  char *uns = alloca (strlen (name) + 10);

  strcpy (uns, "unsigned ");
  strcpy (uns + 9, name);
  return (lookup_typename (uns, (struct block *) NULL, 0));
}