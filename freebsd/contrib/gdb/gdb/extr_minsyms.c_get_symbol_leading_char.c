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
typedef  int /*<<< orphan*/  bfd ;
struct TYPE_2__ {int /*<<< orphan*/ * obfd; } ;

/* Variables and functions */
 int bfd_get_symbol_leading_char (int /*<<< orphan*/ *) ; 
 TYPE_1__* symfile_objfile ; 

__attribute__((used)) static int
get_symbol_leading_char (bfd *abfd)
{
  if (abfd != NULL)
    return bfd_get_symbol_leading_char (abfd);
  if (symfile_objfile != NULL && symfile_objfile->obfd != NULL)
    return bfd_get_symbol_leading_char (symfile_objfile->obfd);
  return 0;
}