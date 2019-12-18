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
typedef  int /*<<< orphan*/  bfd_boolean ;
struct TYPE_3__ {int /*<<< orphan*/  namedata; } ;
typedef  TYPE_1__ Elf_Internal_Note ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  TRUE ; 
 int atoi (char*) ; 
 char* strchr (int /*<<< orphan*/ ,char) ; 

__attribute__((used)) static bfd_boolean
elfcore_netbsd_get_lwpid (Elf_Internal_Note *note, int *lwpidp)
{
  char *cp;

  cp = strchr (note->namedata, '@');
  if (cp != NULL)
    {
      *lwpidp = atoi(cp + 1);
      return TRUE;
    }
  return FALSE;
}