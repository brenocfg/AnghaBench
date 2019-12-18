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
 int /*<<< orphan*/  ASM_FORMAT_PRIVATE_NAME (char*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DECL_ASSEMBLER_NAME (int /*<<< orphan*/ ) ; 
 size_t IDENTIFIER_LENGTH (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IDENTIFIER_POINTER (int /*<<< orphan*/ ) ; 
 char* alloca (int) ; 
 int /*<<< orphan*/  current_function_decl ; 
 int /*<<< orphan*/  get_identifier (char*) ; 
 int /*<<< orphan*/  memcpy (char*,int /*<<< orphan*/ ,size_t) ; 
 int /*<<< orphan*/  strcpy (char*,char*) ; 
 int /*<<< orphan*/  tmp_ompfn_id_num ; 

__attribute__((used)) static tree
create_omp_child_function_name (void)
{
  tree name = DECL_ASSEMBLER_NAME (current_function_decl);
  size_t len = IDENTIFIER_LENGTH (name);
  char *tmp_name, *prefix;

  prefix = alloca (len + sizeof ("_omp_fn"));
  memcpy (prefix, IDENTIFIER_POINTER (name), len);
  strcpy (prefix + len, "_omp_fn");
#ifndef NO_DOT_IN_LABEL
  prefix[len] = '.';
#elif !defined NO_DOLLAR_IN_LABEL
  prefix[len] = '$';
#endif
  ASM_FORMAT_PRIVATE_NAME (tmp_name, prefix, tmp_ompfn_id_num++);
  return get_identifier (tmp_name);
}