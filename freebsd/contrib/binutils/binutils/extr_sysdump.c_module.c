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
 int EOF ; 
 int IT_tr_CODE ; 
 int /*<<< orphan*/  file ; 
 int getc (int /*<<< orphan*/ ) ; 
 scalar_t__ getone (int) ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 int /*<<< orphan*/  tab (int,char*) ; 
 int /*<<< orphan*/  ungetc (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
module (void)
{
  int c = 0;
  int l = 0;

  tab (1, "MODULE***\n");

  do
    {
      c = getc (file);
      ungetc (c, file);

      c &= 0x7f;
    }
  while (getone (c) && c != IT_tr_CODE);

  tab (-1, "");

  c = getc (file);
  while (c != EOF)
    {
      printf ("%02x ", c);
      l++;
      if (l == 32)
	{
	  printf ("\n");
	  l = 0;
	}
      c = getc (file);
    }
}