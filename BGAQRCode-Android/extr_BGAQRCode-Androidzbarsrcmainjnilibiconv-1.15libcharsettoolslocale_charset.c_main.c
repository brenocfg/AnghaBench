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
 int /*<<< orphan*/  LC_ALL ; 
 int /*<<< orphan*/  exit (int /*<<< orphan*/ ) ; 
 char* locale_charset () ; 
 int /*<<< orphan*/  printf (char*,char*) ; 
 int /*<<< orphan*/  setlocale (int /*<<< orphan*/ ,char*) ; 

int main ()
{
  setlocale(LC_ALL, "");
  printf("%s\n", locale_charset());
  exit(0);
}