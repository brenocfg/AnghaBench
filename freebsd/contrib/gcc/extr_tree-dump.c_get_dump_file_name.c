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
struct dump_file_info {scalar_t__ state; scalar_t__ num; int flags; int /*<<< orphan*/  suffix; } ;
typedef  enum tree_dump_index { ____Placeholder_tree_dump_index } tree_dump_index ;
typedef  int /*<<< orphan*/  dump_id ;

/* Variables and functions */
 int TDF_IPA ; 
 int TDF_TREE ; 
 int TDI_none ; 
 char* concat (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dump_base_name ; 
 struct dump_file_info* get_dump_file_info (int) ; 
 scalar_t__ snprintf (char*,int,char*,scalar_t__,char) ; 

char *
get_dump_file_name (enum tree_dump_index phase)
{
  char dump_id[10];
  struct dump_file_info *dfi;

  if (phase == TDI_none)
    return NULL;

  dfi = get_dump_file_info (phase);
  if (dfi->state == 0)
    return NULL;

  if (dfi->num < 0)
    dump_id[0] = '\0';
  else
    {
      char suffix;
      if (dfi->flags & TDF_TREE)
	suffix = 't';
      else if (dfi->flags & TDF_IPA)
	suffix = 'i';
      else
	suffix = 'r';

      if (snprintf (dump_id, sizeof (dump_id), ".%03d%c", dfi->num, suffix) < 0)
	dump_id[0] = '\0';
    }

  return concat (dump_base_name, dump_id, dfi->suffix, NULL);
}