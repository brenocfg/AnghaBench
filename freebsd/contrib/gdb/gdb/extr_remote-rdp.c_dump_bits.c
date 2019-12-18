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
struct yn {int bit; scalar_t__ name; } ;

/* Variables and functions */
 int /*<<< orphan*/  printf_unfiltered (char*,scalar_t__,char*) ; 

__attribute__((used)) static void
dump_bits (struct yn *t, int info)
{
  while (t->name)
    {
      printf_unfiltered ("  %-45s : %s\n", t->name, (info & t->bit) ? "Yes" : "No");
      t++;
    }
}