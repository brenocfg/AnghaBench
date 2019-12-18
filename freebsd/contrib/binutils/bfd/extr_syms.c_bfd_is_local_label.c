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
typedef  int /*<<< orphan*/  bfd ;
struct TYPE_3__ {int flags; int /*<<< orphan*/ * name; } ;
typedef  TYPE_1__ asymbol ;

/* Variables and functions */
 int BSF_FILE ; 
 int BSF_GLOBAL ; 
 int BSF_SECTION_SYM ; 
 int BSF_WEAK ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  bfd_is_local_label_name (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

bfd_boolean
bfd_is_local_label (bfd *abfd, asymbol *sym)
{
  /* The BSF_SECTION_SYM check is needed for IA-64, where every label that
     starts with '.' is local.  This would accidentally catch section names
     if we didn't reject them here.  */
  if ((sym->flags & (BSF_GLOBAL | BSF_WEAK | BSF_FILE | BSF_SECTION_SYM)) != 0)
    return FALSE;
  if (sym->name == NULL)
    return FALSE;
  return bfd_is_local_label_name (abfd, sym->name);
}