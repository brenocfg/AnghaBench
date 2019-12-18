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
struct insn_to_dependency {int type; } ;
typedef  enum insn_type_for_dependency { ____Placeholder_insn_type_for_dependency } insn_type_for_dependency ;

/* Variables and functions */
 int D_all_insn ; 
 int INSN_NAME_LEN ; 
 int /*<<< orphan*/  dependency_insn_hsh ; 
 scalar_t__ hash_find (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  strcpy (char*,char*) ; 

__attribute__((used)) static enum insn_type_for_dependency
dependency_type_from_insn (char *insn_name)
{
  char name[INSN_NAME_LEN];
  const struct insn_to_dependency *tmp;

  strcpy (name, insn_name);
  tmp = (const struct insn_to_dependency *) hash_find (dependency_insn_hsh, name);

  if (tmp)
    return tmp->type;

  return D_all_insn;
}