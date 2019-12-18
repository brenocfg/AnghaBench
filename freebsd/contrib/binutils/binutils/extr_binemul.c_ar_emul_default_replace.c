#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  bfd_boolean ;
struct TYPE_5__ {struct TYPE_5__* archive_next; } ;
typedef  TYPE_1__ bfd ;

/* Variables and functions */
 int /*<<< orphan*/  AR_EMUL_ELEMENT_CHECK (TYPE_1__*,char*) ; 
 int /*<<< orphan*/  AR_EMUL_REPLACE_PRINT_VERBOSE (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  TRUE ; 
 TYPE_1__* bfd_openr (char*,int /*<<< orphan*/ *) ; 

bfd_boolean
ar_emul_default_replace (bfd **after_bfd, char *file_name,
			 bfd_boolean verbose)
{
  bfd *temp;

  temp = *after_bfd;
  *after_bfd = bfd_openr (file_name, NULL);

  AR_EMUL_ELEMENT_CHECK (*after_bfd, file_name);
  AR_EMUL_REPLACE_PRINT_VERBOSE (verbose, file_name);

  (*after_bfd)->archive_next = temp;

  return TRUE;
}