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
typedef  int /*<<< orphan*/  bfd ;

/* Variables and functions */
 int get_file_size (char const*) ; 
 int /*<<< orphan*/ * open_inarch (char const*,char*) ; 
 int /*<<< orphan*/  write_archive (int /*<<< orphan*/ *) ; 
 int write_armap ; 
 int /*<<< orphan*/  xexit (int) ; 

__attribute__((used)) static int
ranlib_only (const char *archname)
{
  bfd *arch;

  if (get_file_size (archname) < 1)
    return 1;
  write_armap = 1;
  arch = open_inarch (archname, (char *) NULL);
  if (arch == NULL)
    xexit (1);
  write_archive (arch);
  return 0;
}