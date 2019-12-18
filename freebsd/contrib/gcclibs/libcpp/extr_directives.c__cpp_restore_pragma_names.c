#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  pragmas; } ;
typedef  TYPE_1__ cpp_reader ;

/* Variables and functions */
 int /*<<< orphan*/  free (char**) ; 
 int /*<<< orphan*/  restore_registered_pragmas (TYPE_1__*,int /*<<< orphan*/ ,char**) ; 

void
_cpp_restore_pragma_names (cpp_reader *pfile, char **saved)
{
  (void) restore_registered_pragmas (pfile, pfile->pragmas, saved);
  free (saved);
}