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
 int DisaPc ; 
 scalar_t__ DisaWord (int) ; 
 int /*<<< orphan*/  sprintf (char*,char*,int) ; 

__attribute__((used)) static void GetOffset(char *text)
{
  int off=(short)DisaWord(DisaPc); DisaPc+=2;

  if (off<0) sprintf(text,"-$%x",-off);
  else       sprintf(text,"$%x",  off);
}