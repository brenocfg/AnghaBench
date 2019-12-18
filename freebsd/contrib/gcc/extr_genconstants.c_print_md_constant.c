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
struct md_constant {char* name; char* value; } ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ *,char*,char*,char*) ; 

__attribute__((used)) static int
print_md_constant (void **slot, void *info)
{
  struct md_constant *def = (struct md_constant *) *slot;
  FILE *file = (FILE *) info;

  fprintf (file, "#define %s %s\n", def->name, def->value);
  return 1;
}