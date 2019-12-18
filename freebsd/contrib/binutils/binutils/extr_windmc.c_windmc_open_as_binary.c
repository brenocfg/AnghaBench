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
 int /*<<< orphan*/ * bfd_openw (char const*,char*) ; 
 int /*<<< orphan*/  fatal (char*,char const*) ; 

__attribute__((used)) static bfd *
windmc_open_as_binary (const char *filename)
{
  bfd *abfd;

  abfd = bfd_openw (filename, "binary");
  if (! abfd)
    fatal ("can't open `%s' for output", filename);

  return abfd;
}