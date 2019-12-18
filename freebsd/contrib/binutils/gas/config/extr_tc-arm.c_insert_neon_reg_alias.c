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
struct reg_entry {struct neon_typed_alias* neon; } ;
struct neon_typed_alias {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  _ (char*) ; 
 int /*<<< orphan*/  first_error (int /*<<< orphan*/ ) ; 
 struct reg_entry* insert_reg_alias (char*,int,int) ; 
 struct neon_typed_alias* xmalloc (int) ; 

__attribute__((used)) static void
insert_neon_reg_alias (char *str, int number, int type,
                       struct neon_typed_alias *atype)
{
  struct reg_entry *reg = insert_reg_alias (str, number, type);
  
  if (!reg)
    {
      first_error (_("attempt to redefine typed alias"));
      return;
    }
  
  if (atype)
    {
      reg->neon = xmalloc (sizeof (struct neon_typed_alias));
      *reg->neon = *atype;
    }
}