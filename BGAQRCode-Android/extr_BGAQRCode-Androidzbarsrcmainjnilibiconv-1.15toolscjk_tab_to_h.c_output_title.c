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
 int /*<<< orphan*/  printf (char*,...) ; 

__attribute__((used)) static void output_title (const char *charsetname)
{
  printf("/*\n");
  printf(" * Copyright (C) 1999-2016 Free Software Foundation, Inc.\n");
  printf(" * This file is part of the GNU LIBICONV Library.\n");
  printf(" *\n");
  printf(" * The GNU LIBICONV Library is free software; you can redistribute it\n");
  printf(" * and/or modify it under the terms of the GNU Library General Public\n");
  printf(" * License as published by the Free Software Foundation; either version 2\n");
  printf(" * of the License, or (at your option) any later version.\n");
  printf(" *\n");
  printf(" * The GNU LIBICONV Library is distributed in the hope that it will be\n");
  printf(" * useful, but WITHOUT ANY WARRANTY; without even the implied warranty of\n");
  printf(" * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU\n");
  printf(" * Library General Public License for more details.\n");
  printf(" *\n");
  printf(" * You should have received a copy of the GNU Library General Public\n");
  printf(" * License along with the GNU LIBICONV Library; see the file COPYING.LIB.\n");
  printf(" * If not, see <http://www.gnu.org/licenses/>.\n");
  printf(" */\n");
  printf("\n");
  printf("/*\n");
  printf(" * %s\n", charsetname);
  printf(" */\n");
  printf("\n");
}