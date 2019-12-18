#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ tree ;
struct TYPE_2__ {int unqiue_block_number; } ;

/* Variables and functions */
 scalar_t__ DECL_CONTEXT (scalar_t__) ; 
 int /*<<< orphan*/  DECL_NAME (scalar_t__) ; 
 TYPE_1__* DECL_STRUCT_FUNCTION (scalar_t__) ; 
 scalar_t__ FUNCTION_DECL ; 
 int IDENTIFIER_LENGTH (int /*<<< orphan*/ ) ; 
 char* IDENTIFIER_POINTER (int /*<<< orphan*/ ) ; 
 scalar_t__ TREE_CODE (scalar_t__) ; 
 scalar_t__ alloca (int) ; 
 scalar_t__ current_function_decl ; 
 scalar_t__ get_identifier (char*) ; 
 int /*<<< orphan*/  sprintf (char*,char*,...) ; 

tree
build_block_helper_name (int unique_count)
{
  char *buf;
  if (!current_function_decl)
    {
      /* APPLE LOCAL begin radar 6411649 */
      static int global_count;
      buf = (char *)alloca (32);
      sprintf (buf, "__block_global_%d", ++global_count);
      /* APPLE LOCAL end radar 6411649 */
    }
  else
    {
      tree outer_decl = current_function_decl;
      /* APPLE LOCAL begin radar 6169580 */
      while (outer_decl &&
	      DECL_CONTEXT (outer_decl) && TREE_CODE (DECL_CONTEXT (outer_decl)) == FUNCTION_DECL)
      /* APPLE LOCAL end radar 6169580 */
	 outer_decl = DECL_CONTEXT (outer_decl);
      /* APPLE LOCAL begin radar 6411649 */
      if (!unique_count)
	 unique_count = ++DECL_STRUCT_FUNCTION(outer_decl)->unqiue_block_number;
      /* APPLE LOCAL end radar 6411649 */
      buf = (char *)alloca (IDENTIFIER_LENGTH (DECL_NAME (outer_decl)) + 32); 
      sprintf (buf, "__%s_block_invoke_%d", 
	       IDENTIFIER_POINTER (DECL_NAME (outer_decl)), unique_count);
    }
   return get_identifier (buf); 
}