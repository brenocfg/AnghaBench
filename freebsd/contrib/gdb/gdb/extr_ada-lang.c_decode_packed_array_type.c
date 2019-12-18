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
 scalar_t__ DEPRECATED_STREQ (char*,char*) ; 
 scalar_t__ LOC_TYPEDEF ; 
 scalar_t__ SYMBOL_CLASS (struct symbol*) ; 
 struct type* SYMBOL_TYPE (struct symbol*) ; 
 scalar_t__ TYPE_CODE (struct type*) ; 
 scalar_t__ TYPE_CODE_ARRAY ; 
 int /*<<< orphan*/  VAR_DOMAIN ; 
 int ada_lookup_symbol_list (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct symbol***,struct block***) ; 
 char* ada_type_name (struct type*) ; 
 scalar_t__ alloca (scalar_t__) ; 
 struct type* check_typedef (struct type*) ; 
 int /*<<< orphan*/  get_selected_block (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memcpy (char*,char const*,int) ; 
 struct type* packed_array_type (struct type*,long*) ; 
 int sscanf (char*,char*,long*) ; 
 scalar_t__ strlen (char const*) ; 
 char* strstr (char const*,char*) ; 
 int /*<<< orphan*/  warning (char*) ; 

__attribute__((used)) static struct type *
decode_packed_array_type (struct type *type)
{
  struct symbol **syms;
  struct block **blocks;
  const char *raw_name = ada_type_name (check_typedef (type));
  char *name = (char *) alloca (strlen (raw_name) + 1);
  char *tail = strstr (raw_name, "___XP");
  struct type *shadow_type;
  long bits;
  int i, n;

  memcpy (name, raw_name, tail - raw_name);
  name[tail - raw_name] = '\000';

  /* NOTE: Use ada_lookup_symbol_list because of bug in some versions
   * of gcc (Solaris, e.g.). FIXME when compiler is fixed. */
  n = ada_lookup_symbol_list (name, get_selected_block (NULL),
			      VAR_DOMAIN, &syms, &blocks);
  for (i = 0; i < n; i += 1)
    if (syms[i] != NULL && SYMBOL_CLASS (syms[i]) == LOC_TYPEDEF
	&& DEPRECATED_STREQ (name, ada_type_name (SYMBOL_TYPE (syms[i]))))
      break;
  if (i >= n)
    {
      warning ("could not find bounds information on packed array");
      return NULL;
    }
  shadow_type = SYMBOL_TYPE (syms[i]);

  if (TYPE_CODE (shadow_type) != TYPE_CODE_ARRAY)
    {
      warning ("could not understand bounds information on packed array");
      return NULL;
    }

  if (sscanf (tail + sizeof ("___XP") - 1, "%ld", &bits) != 1)
    {
      warning ("could not understand bit size information on packed array");
      return NULL;
    }

  return packed_array_type (shadow_type, &bits);
}