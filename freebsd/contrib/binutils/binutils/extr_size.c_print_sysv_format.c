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
typedef  scalar_t__ bfd_size_type ;
typedef  int /*<<< orphan*/  bfd ;

/* Variables and functions */
 char* bfd_get_filename (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bfd_map_over_sections (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * bfd_my_archive (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 int /*<<< orphan*/  rprint_number (char*,scalar_t__) ; 
 void* size_number (scalar_t__) ; 
 scalar_t__ svi_maxvma ; 
 char* svi_namelen ; 
 char* svi_sizelen ; 
 scalar_t__ svi_total ; 
 void* svi_vmalen ; 
 int /*<<< orphan*/  sysv_internal_printer ; 
 int /*<<< orphan*/  sysv_internal_sizer ; 

__attribute__((used)) static void
print_sysv_format (bfd *file)
{
  /* Size all of the columns.  */
  svi_total = 0;
  svi_maxvma = 0;
  svi_namelen = 0;
  bfd_map_over_sections (file, sysv_internal_sizer, NULL);
  svi_vmalen = size_number ((bfd_size_type)svi_maxvma);

  if ((size_t) svi_vmalen < sizeof ("addr") - 1)
    svi_vmalen = sizeof ("addr")-1;

  svi_sizelen = size_number (svi_total);
  if ((size_t) svi_sizelen < sizeof ("size") - 1)
    svi_sizelen = sizeof ("size")-1;

  svi_total = 0;
  printf ("%s  ", bfd_get_filename (file));

  if (bfd_my_archive (file))
    printf (" (ex %s)", bfd_get_filename (bfd_my_archive (file)));

  printf (":\n%-*s   %*s   %*s\n", svi_namelen, "section",
	  svi_sizelen, "size", svi_vmalen, "addr");

  bfd_map_over_sections (file, sysv_internal_printer, NULL);

  printf ("%-*s   ", svi_namelen, "Total");
  rprint_number (svi_sizelen, svi_total);
  printf ("\n\n");
}