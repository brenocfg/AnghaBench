#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int chosen; int /*<<< orphan*/ * file; } ;
typedef  TYPE_1__ symbol ;
typedef  int /*<<< orphan*/  file ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int /*<<< orphan*/  file_push (int /*<<< orphan*/ *) ; 
 TYPE_1__* symbol_hash_lookup (char const*,int) ; 
 int /*<<< orphan*/  symbol_push (TYPE_1__*) ; 
 char* tfgets (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
freadsym (FILE *stream, file *f, int chosen)
{
  symbol *sym;

  {
    const char *name = tfgets (stream);
    sym = symbol_hash_lookup (name, true);
  }

  if (sym->file == NULL)
    {
      /* We didn't have this symbol already, so we choose this file.  */

      symbol_push (sym);
      sym->file = f;
      sym->chosen = chosen;
    }
  else if (chosen)
    {
      /* We want this file; cast aside any pretender.  */

      if (sym->chosen && sym->file != f)
	{
	  if (sym->chosen == 1)
	    file_push (sym->file);
	  else
	    {
	      file_push (f);
	      f = sym->file;
	      chosen = sym->chosen;
	    }
	}
      sym->file = f;
      sym->chosen = chosen;
    }
}