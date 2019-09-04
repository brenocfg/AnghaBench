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
 int /*<<< orphan*/  EXIT_SUCCESS ; 
 char* _ (char*) ; 
 int _libiconv_version ; 
 int /*<<< orphan*/  exit (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fputs (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 int /*<<< orphan*/  stdout ; 

__attribute__((used)) static void print_version (void)
{
  printf("iconv (GNU libiconv %d.%d)\n",
         _libiconv_version >> 8, _libiconv_version & 0xff);
  printf("Copyright (C) %s Free Software Foundation, Inc.\n", "2000-2017");
  /* xgettext: no-wrap */
  fputs (_("\
License GPLv3+: GNU GPL version 3 or later <http://gnu.org/licenses/gpl.html>\n\
This is free software: you are free to change and redistribute it.\n\
There is NO WARRANTY, to the extent permitted by law.\n\
"),stdout);
  /* TRANSLATORS: The %s placeholder expands to an author's name.  */
  printf(_("Written by %s.\n"),"Bruno Haible");
  exit(EXIT_SUCCESS);
}