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
typedef  int /*<<< orphan*/  lang_input_statement_type ;
struct TYPE_2__ {int (* find_potential_libraries ) (char*,int /*<<< orphan*/ *) ;} ;

/* Variables and functions */
 TYPE_1__* ld_emulation ; 
 int stub1 (char*,int /*<<< orphan*/ *) ; 

int
ldemul_find_potential_libraries (char *name, lang_input_statement_type *entry)
{
  if (ld_emulation->find_potential_libraries)
    return ld_emulation->find_potential_libraries (name, entry);

  return 0;
}