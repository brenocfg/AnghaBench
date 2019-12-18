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
 char* COPYRIGHT_YEAR ; 
 char* PROG_NAME ; 
 char* VER_NAME ; 
 int /*<<< orphan*/  exit (int) ; 
 int /*<<< orphan*/  printf (char*,char*,...) ; 

void ProgramUsage()
{
   printf("%s v%s - by Cyber Warrior X (c)%s\n", PROG_NAME, VER_NAME, COPYRIGHT_YEAR);
   printf("usage: %s <core index as specified in pertest.c>\n", PROG_NAME);
   exit (1);
}