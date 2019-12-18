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
struct fn_decl {int /*<<< orphan*/  fname; } ;

/* Variables and functions */
 int HASH_SIZE ; 
 int /*<<< orphan*/  gcc_assert (int) ; 
 size_t* hash_tab ; 
 int hashstr (char const*,int) ; 
 struct fn_decl* std_protos ; 
 scalar_t__ strlen (int /*<<< orphan*/ ) ; 
 scalar_t__ strncmp (int /*<<< orphan*/ ,char const*,int) ; 

__attribute__((used)) static struct fn_decl *
lookup_std_proto (const char *name, int name_length)
{
  int i = hashstr (name, name_length) % HASH_SIZE;
  int i0 = i;
  for (;;)
    {
      struct fn_decl *fn;
      if (hash_tab[i] == 0)
	return NULL;
      fn = &std_protos[hash_tab[i]];
      if ((int) strlen (fn->fname) == name_length
	  && strncmp (fn->fname, name, name_length) == 0)
	return fn;
      i = (i+1) % HASH_SIZE;
      gcc_assert (i != i0);
    }
}