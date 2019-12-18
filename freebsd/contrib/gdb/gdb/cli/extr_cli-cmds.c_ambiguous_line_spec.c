#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct symtabs_and_lines {int nelts; TYPE_2__* sals; } ;
struct TYPE_4__ {int /*<<< orphan*/  line; TYPE_1__* symtab; } ;
struct TYPE_3__ {int /*<<< orphan*/  filename; } ;

/* Variables and functions */
 int /*<<< orphan*/  printf_filtered (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
ambiguous_line_spec (struct symtabs_and_lines *sals)
{
  int i;

  for (i = 0; i < sals->nelts; ++i)
    printf_filtered ("file: \"%s\", line number: %d\n",
		     sals->sals[i].symtab->filename, sals->sals[i].line);
}