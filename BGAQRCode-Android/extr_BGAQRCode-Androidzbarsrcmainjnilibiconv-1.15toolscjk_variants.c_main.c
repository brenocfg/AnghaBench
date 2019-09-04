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
 int ENTRIES ; 
 int EOF ; 
 int MAX_PER_ENTRY ; 
 int /*<<< orphan*/  exit (int) ; 
 int getc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 int scanf (char*,int*) ; 
 int /*<<< orphan*/  stdin ; 
 int /*<<< orphan*/  ungetc (int,int /*<<< orphan*/ ) ; 

int main (int argc, char *argv[])
{
  int variants[MAX_PER_ENTRY*ENTRIES];
  int uni2index[0x10000];
  int index;

  if (argc != 1)
    exit(1);

  printf("/*\n");
  printf(" * Copyright (C) 1999-2002 Free Software Foundation, Inc.\n");
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
  printf(" * CJK variants table\n");
  printf(" */\n");
  printf("\n");
  {
    int c;
    int j;
    for (j = 0; j < 0x10000; j++)
      uni2index[j] = -1;
    index = 0;
    for (;;) {
      c = getc(stdin);
      if (c == EOF)
        break;
      if (c == '#') {
        do { c = getc(stdin); } while (!(c == EOF || c == '\n'));
        continue;
      }
      ungetc(c,stdin);
      if (scanf("%x",&j) != 1)
        exit(1);
      c = getc(stdin);
      if (c != '\t')
        exit(1);
      uni2index[j] = index;
      for (;;) {
        int i;
        if (scanf("%x",&i) != 1)
          exit(1);
        if (!(i >= 0x3000 && i < 0x3000+0x8000))
          exit(1);
        variants[index++] = i-0x3000;
        c = getc(stdin);
        if (c != ' ')
          break;
      }
      variants[index-1] |= 0x8000; /* end of list marker */
      if (c != '\n')
        exit(1);
    }
  }
  printf("static const unsigned short cjk_variants[%d] = {",index);
  {
    int i;
    for (i = 0; i < index; i++) {
      if ((i % 8) == 0)
        printf("\n ");
      printf(" 0x%04x,",variants[i]);
    }
    printf("\n};\n");
  }
  printf("\n");
  printf("static const short cjk_variants_indx[0x5200] = {\n");
  {
    int j;
    for (j = 0x4e00; j < 0xa000; j++) {
      if ((j % 0x100) == 0)
        printf("  /* 0x%04x */\n", j);
      if ((j % 8) == 0)
        printf(" ");
      printf(" %5d,",uni2index[j]);
      if ((j % 8) == 7)
        printf("\n");
    }
    printf("};\n");
  }
  printf("\n");

  return 0;
}