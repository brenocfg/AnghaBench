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
typedef  int /*<<< orphan*/  bfd_size_type ;
typedef  int /*<<< orphan*/  bfd_boolean ;
typedef  int /*<<< orphan*/  bfd ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  _bfd_construct_extended_name_table (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char**,int /*<<< orphan*/ *) ; 

bfd_boolean
_bfd_archive_bsd_construct_extended_name_table (bfd *abfd,
						char **tabloc,
						bfd_size_type *tablen,
						const char **name)
{
  *name = "ARFILENAMES/";
  return _bfd_construct_extended_name_table (abfd, FALSE, tabloc, tablen);
}