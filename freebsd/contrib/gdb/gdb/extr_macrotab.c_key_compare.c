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
struct macro_source_file {int dummy; } ;
struct macro_key {int /*<<< orphan*/  start_line; int /*<<< orphan*/  start_file; int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int compare_locations (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct macro_source_file*,int) ; 
 int strcmp (int /*<<< orphan*/ ,char const*) ; 

__attribute__((used)) static int
key_compare (struct macro_key *key,
             const char *name, struct macro_source_file *file, int line)
{
  int names = strcmp (key->name, name);
  if (names)
    return names;

  return compare_locations (key->start_file, key->start_line,
                            file, line);
}