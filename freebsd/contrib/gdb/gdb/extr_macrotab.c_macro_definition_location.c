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
struct macro_source_file {int dummy; } ;
struct macro_key {int start_line; struct macro_source_file* start_file; } ;
typedef  TYPE_1__* splay_tree_node ;
struct TYPE_3__ {scalar_t__ key; } ;

/* Variables and functions */
 TYPE_1__* find_definition (char const*,struct macro_source_file*,int) ; 

struct macro_source_file *
macro_definition_location (struct macro_source_file *source,
                           int line,
                           const char *name,
                           int *definition_line)
{
  splay_tree_node n = find_definition (name, source, line);

  if (n)
    {
      struct macro_key *key = (struct macro_key *) n->key;
      *definition_line = key->start_line;
      return key->start_file;
    }
  else
    return 0;
}