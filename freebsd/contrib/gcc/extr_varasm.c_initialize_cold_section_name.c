#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ tree ;
struct TYPE_4__ {scalar_t__ unlikely_text_section_name; } ;
struct TYPE_3__ {char* (* strip_name_encoding ) (char*) ;} ;

/* Variables and functions */
 char* ACONCAT (char const*) ; 
 scalar_t__ DECL_SECTION_NAME (scalar_t__) ; 
 scalar_t__ TREE_STRING_LENGTH (scalar_t__) ; 
 int /*<<< orphan*/  TREE_STRING_POINTER (scalar_t__) ; 
 scalar_t__ UNLIKELY_EXECUTED_TEXT_SECTION_NAME ; 
 char* alloca (scalar_t__) ; 
 TYPE_2__* cfun ; 
 scalar_t__ current_function_decl ; 
 scalar_t__ flag_function_sections ; 
 int /*<<< orphan*/  gcc_assert (int) ; 
 scalar_t__ ggc_strdup (char*) ; 
 int /*<<< orphan*/  memcpy (char*,int /*<<< orphan*/ ,scalar_t__) ; 
 char* stub1 (char*) ; 
 TYPE_1__ targetm ; 

__attribute__((used)) static void
initialize_cold_section_name (void)
{
  const char *stripped_name;
  char *name, *buffer;
  tree dsn;

  gcc_assert (cfun && current_function_decl);
  if (cfun->unlikely_text_section_name)
    return;

  dsn = DECL_SECTION_NAME (current_function_decl);
  if (flag_function_sections && dsn)
    {
      name = alloca (TREE_STRING_LENGTH (dsn) + 1);
      memcpy (name, TREE_STRING_POINTER (dsn), TREE_STRING_LENGTH (dsn) + 1);

      stripped_name = targetm.strip_name_encoding (name);

      buffer = ACONCAT ((stripped_name, "_unlikely", NULL));
      cfun->unlikely_text_section_name = ggc_strdup (buffer);
    }
  else
    cfun->unlikely_text_section_name =  UNLIKELY_EXECUTED_TEXT_SECTION_NAME;
}