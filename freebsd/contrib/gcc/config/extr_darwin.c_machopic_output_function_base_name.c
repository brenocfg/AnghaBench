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
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int /*<<< orphan*/  DECL_ASSEMBLER_NAME (int /*<<< orphan*/ ) ; 
 char* IDENTIFIER_POINTER (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MACHO_DYNAMIC_NO_PIC_P ; 
 int /*<<< orphan*/  current_function_decl ; 
 int current_pic_label_num ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ *,char*,int) ; 
 char const* function_base_func_name ; 
 int /*<<< orphan*/  gcc_assert (int) ; 

void
machopic_output_function_base_name (FILE *file)
{
  const char *current_name;

  /* If dynamic-no-pic is on, we should not get here.  */
  gcc_assert (!MACHO_DYNAMIC_NO_PIC_P);
  current_name =
    IDENTIFIER_POINTER (DECL_ASSEMBLER_NAME (current_function_decl));
  if (function_base_func_name != current_name)
    {
      ++current_pic_label_num;
      function_base_func_name = current_name;
    }
  fprintf (file, "\"L%011d$pb\"", current_pic_label_num);
}