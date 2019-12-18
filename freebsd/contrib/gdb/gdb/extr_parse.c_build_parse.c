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
typedef  int /*<<< orphan*/  TYPE_TARGET_TYPE ;

/* Variables and functions */
 int HOST_CHAR_BIT ; 
 int TARGET_INT_BIT ; 
 int /*<<< orphan*/  TYPE_CODE_FUNC ; 
 int /*<<< orphan*/  TYPE_CODE_INT ; 
 int /*<<< orphan*/  builtin_type_int ; 
 void* init_type (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *) ; 
 void* msym_data_symbol_type ; 
 int /*<<< orphan*/  msym_text_symbol_type ; 
 void* msym_unknown_symbol_type ; 

__attribute__((used)) static void
build_parse (void)
{
  int i;

  msym_text_symbol_type =
    init_type (TYPE_CODE_FUNC, 1, 0, "<text variable, no debug info>", NULL);
  TYPE_TARGET_TYPE (msym_text_symbol_type) = builtin_type_int;
  msym_data_symbol_type =
    init_type (TYPE_CODE_INT, TARGET_INT_BIT / HOST_CHAR_BIT, 0,
	       "<data variable, no debug info>", NULL);
  msym_unknown_symbol_type =
    init_type (TYPE_CODE_INT, 1, 0,
	       "<variable (not text or data), no debug info>",
	       NULL);
}