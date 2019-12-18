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
struct dump_file_info {int state; int flags; } ;
typedef  enum tree_dump_index { ____Placeholder_tree_dump_index } tree_dump_index ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int TDI_none ; 
 int /*<<< orphan*/  dump_enabled_p (int) ; 
 int /*<<< orphan*/  errno ; 
 int /*<<< orphan*/  error (char*,char*,char*) ; 
 int /*<<< orphan*/ * fopen (char*,char*) ; 
 int /*<<< orphan*/  free (char*) ; 
 struct dump_file_info* get_dump_file_info (int) ; 
 char* get_dump_file_name (int) ; 
 char* strerror (int /*<<< orphan*/ ) ; 

FILE *
dump_begin (enum tree_dump_index phase, int *flag_ptr)
{
  char *name;
  struct dump_file_info *dfi;
  FILE *stream;

  if (phase == TDI_none || !dump_enabled_p (phase))
    return NULL;

  name = get_dump_file_name (phase);
  dfi = get_dump_file_info (phase);
  stream = fopen (name, dfi->state < 0 ? "w" : "a");
  if (!stream)
    error ("could not open dump file %qs: %s", name, strerror (errno));
  else
    dfi->state = 1;
  free (name);

  if (flag_ptr)
    *flag_ptr = dfi->flags;

  return stream;
}