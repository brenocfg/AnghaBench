#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int tweaked; scalar_t__ tweaking; int /*<<< orphan*/ * file; } ;
typedef  TYPE_1__ symbol ;
typedef  int /*<<< orphan*/  file ;

/* Variables and functions */
 TYPE_1__* symbol_hash_lookup (char*,int) ; 

__attribute__((used)) static void
maybe_tweak (char *line, file *f)
{
  symbol *sym = symbol_hash_lookup (line + 2, false);

  if ((sym->file == f && sym->tweaking)
      || (sym->file != f && line[0] == 'C'))
    {
      sym->tweaking = 0;
      sym->tweaked = 1;

      if (line[0] == 'O')
	line[0] = 'C';
      else
	line[0] = 'O';
    }
}