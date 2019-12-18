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

/* Variables and functions */
 char* bfd_get_filename (scalar_t__) ; 
 int /*<<< orphan*/  error (char*) ; 
 scalar_t__ exec_bfd ; 

char *
get_exec_file (int err)
{
  if (exec_bfd)
    return bfd_get_filename (exec_bfd);
  if (!err)
    return NULL;

  error ("No executable file specified.\n\
Use the \"file\" or \"exec-file\" command.");
  return NULL;
}