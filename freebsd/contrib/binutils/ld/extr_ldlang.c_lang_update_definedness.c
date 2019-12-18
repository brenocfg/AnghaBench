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
struct lang_definedness_hash_entry {int iteration; } ;
struct bfd_link_hash_entry {scalar_t__ type; } ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 scalar_t__ bfd_hash_lookup (int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ bfd_link_hash_common ; 
 scalar_t__ bfd_link_hash_new ; 
 scalar_t__ bfd_link_hash_undefined ; 
 int /*<<< orphan*/  lang_definedness_table ; 
 int lang_statement_iteration ; 

void
lang_update_definedness (const char *name, struct bfd_link_hash_entry *h)
{
  struct lang_definedness_hash_entry *defentry
    = (struct lang_definedness_hash_entry *)
    bfd_hash_lookup (&lang_definedness_table, name, FALSE, FALSE);

  /* We don't keep track of symbols not tested with DEFINED.  */
  if (defentry == NULL)
    return;

  /* If the symbol was already defined, and not from an earlier statement
     iteration, don't update the definedness iteration, because that'd
     make the symbol seem defined in the linker script at this point, and
     it wasn't; it was defined in some object.  If we do anyway, DEFINED
     would start to yield false before this point and the construct "sym =
     DEFINED (sym) ? sym : X;" would change sym to X despite being defined
     in an object.  */
  if (h->type != bfd_link_hash_undefined
      && h->type != bfd_link_hash_common
      && h->type != bfd_link_hash_new
      && defentry->iteration == -1)
    return;

  defentry->iteration = lang_statement_iteration;
}