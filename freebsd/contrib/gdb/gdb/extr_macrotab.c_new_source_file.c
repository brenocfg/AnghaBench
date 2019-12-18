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
struct macro_table {int dummy; } ;
struct macro_source_file {scalar_t__ includes; int /*<<< orphan*/  filename; struct macro_table* table; } ;

/* Variables and functions */
 struct macro_source_file* macro_alloc (int,struct macro_table*) ; 
 int /*<<< orphan*/  macro_bcache_str (struct macro_table*,char const*) ; 
 int /*<<< orphan*/  memset (struct macro_source_file*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static struct macro_source_file *
new_source_file (struct macro_table *t,
                 const char *filename)
{
  /* Get space for the source file structure itself.  */
  struct macro_source_file *f = macro_alloc (sizeof (*f), t);

  memset (f, 0, sizeof (*f));
  f->table = t;
  f->filename = macro_bcache_str (t, filename);
  f->includes = 0;

  return f;
}