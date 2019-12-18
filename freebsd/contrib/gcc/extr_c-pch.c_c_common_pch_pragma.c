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
typedef  int /*<<< orphan*/  cpp_reader ;
struct TYPE_2__ {int /*<<< orphan*/  warn_invalid_pch; int /*<<< orphan*/  preprocessed; } ;

/* Variables and functions */
 int O_BINARY ; 
 int O_RDONLY ; 
 int /*<<< orphan*/  c_common_read_pch (int /*<<< orphan*/ *,char const*,int,char const*) ; 
 int c_common_valid_pch (int /*<<< orphan*/ *,char const*,int) ; 
 int /*<<< orphan*/  close (int) ; 
 TYPE_1__* cpp_get_options (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  error (char*) ; 
 int /*<<< orphan*/  fatal_error (char*,char const*) ; 
 int /*<<< orphan*/  inform (char*) ; 
 int open (char const*,int,int) ; 

void
c_common_pch_pragma (cpp_reader *pfile, const char *name)
{
  int fd;

  if (!cpp_get_options (pfile)->preprocessed)
    {
      error ("pch_preprocess pragma should only be used with -fpreprocessed");
      inform ("use #include instead");
      return;
    }

  fd = open (name, O_RDONLY | O_BINARY, 0666);
  if (fd == -1)
    fatal_error ("%s: couldn%'t open PCH file: %m", name);

  if (c_common_valid_pch (pfile, name, fd) != 1)
    {
      if (!cpp_get_options (pfile)->warn_invalid_pch)
	inform ("use -Winvalid-pch for more information");
      fatal_error ("%s: PCH file was invalid", name);
    }

  c_common_read_pch (pfile, name, fd, name);

  close (fd);
}