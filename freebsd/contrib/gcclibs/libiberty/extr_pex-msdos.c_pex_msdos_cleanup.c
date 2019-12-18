#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct pex_obj {int /*<<< orphan*/ * sysdep; } ;
struct pex_msdos {int dummy; } ;
struct TYPE_3__ {struct TYPE_3__* statuses; struct TYPE_3__** files; } ;

/* Variables and functions */
 int PEX_MSDOS_FILE_COUNT ; 
 int /*<<< orphan*/  free (TYPE_1__*) ; 
 TYPE_1__* msdos ; 

__attribute__((used)) static void
pex_msdos_cleanup (struct pex_obj  *obj)
{
  struct pex_msdos *ms;
  int i;

  ms = (struct pex_msdos *) obj->sysdep;
  for (i = 0; i < PEX_MSDOS_FILE_COUNT; ++i)
    if (msdos->files[i] != NULL)
      free (msdos->files[i]);
  if (msdos->statuses != NULL)
    free (msdos->statuses);
  free (msdos);
  obj->sysdep = NULL;
}