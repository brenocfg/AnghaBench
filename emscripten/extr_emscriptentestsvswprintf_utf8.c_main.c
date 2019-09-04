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
 int /*<<< orphan*/  setlocale (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  test_vswprintf (char*,int) ; 

int main ()
{
  setlocale(LC_ALL, "");
  test_vswprintf(L"This is a character: %lc.\n", 0xF6 /* Unicode Character 'LATIN SMALL LETTER O WITH DIAERESIS' (U+00F6): http://www.fileformat.info/info/unicode/char/00f6/index.htm */);
  return 0;
}