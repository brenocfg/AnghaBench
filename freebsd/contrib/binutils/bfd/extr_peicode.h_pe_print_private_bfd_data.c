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
typedef  int /*<<< orphan*/  bfd_boolean ;
typedef  int /*<<< orphan*/  bfd ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  _bfd_XX_print_private_bfd_data_common (int /*<<< orphan*/ *,void*) ; 
 int /*<<< orphan*/  fputc (char,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pe_saved_coff_bfd_print_private_bfd_data (int /*<<< orphan*/ *,void*) ; 

__attribute__((used)) static bfd_boolean
pe_print_private_bfd_data (bfd *abfd, void * vfile)
{
  FILE *file = (FILE *) vfile;

  if (!_bfd_XX_print_private_bfd_data_common (abfd, vfile))
    return FALSE;

  if (pe_saved_coff_bfd_print_private_bfd_data == NULL)
    return TRUE;

  fputc ('\n', file);

  return pe_saved_coff_bfd_print_private_bfd_data (abfd, vfile);
}