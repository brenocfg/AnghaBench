#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {scalar_t__ local_toc_sym_map; scalar_t__ relocbase; int /*<<< orphan*/ * raw_syments; int /*<<< orphan*/ * conversion_table; int /*<<< orphan*/ * symbols; } ;
typedef  TYPE_2__ coff_data_type ;
typedef  int bfd_size_type ;
typedef  int /*<<< orphan*/  bfd_boolean ;
struct TYPE_8__ {int /*<<< orphan*/ * coff_obj_data; } ;
struct TYPE_10__ {TYPE_1__ tdata; } ;
typedef  TYPE_3__ bfd ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/ * bfd_zalloc (TYPE_3__*,int) ; 
 TYPE_2__* coff_data (TYPE_3__*) ; 

__attribute__((used)) static bfd_boolean
coff_mkobject (bfd * abfd)
{
  coff_data_type *coff;
  bfd_size_type amt = sizeof (coff_data_type);

  abfd->tdata.coff_obj_data = bfd_zalloc (abfd, amt);
  if (abfd->tdata.coff_obj_data == NULL)
    return FALSE;
  coff = coff_data (abfd);
  coff->symbols = NULL;
  coff->conversion_table = NULL;
  coff->raw_syments = NULL;
  coff->relocbase = 0;
  coff->local_toc_sym_map = 0;

/*  make_abs_section(abfd);*/

  return TRUE;
}