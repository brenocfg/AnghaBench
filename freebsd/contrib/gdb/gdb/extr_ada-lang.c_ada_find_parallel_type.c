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
struct symbol {int dummy; } ;
struct block {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  GROW_VECT (char*,size_t,int) ; 
 struct type* ada_find_any_type (char*) ; 
 char* ada_type_name (struct type*) ; 
 int /*<<< orphan*/  strcpy (char*,char const*) ; 
 int strlen (char const*) ; 

struct type *
ada_find_parallel_type (struct type *type, const char *suffix)
{
  static char *name;
  static size_t name_len = 0;
  struct symbol **syms;
  struct block **blocks;
  int nsyms;
  int len;
  char *typename = ada_type_name (type);

  if (typename == NULL)
    return NULL;

  len = strlen (typename);

  GROW_VECT (name, name_len, len + strlen (suffix) + 1);

  strcpy (name, typename);
  strcpy (name + len, suffix);

  return ada_find_any_type (name);
}