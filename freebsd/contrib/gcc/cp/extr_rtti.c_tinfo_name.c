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
typedef  int /*<<< orphan*/  tree ;

/* Variables and functions */
 int /*<<< orphan*/  build_string (scalar_t__,char const*) ; 
 int /*<<< orphan*/  fix_string_type (int /*<<< orphan*/ ) ; 
 char* mangle_type_string (int /*<<< orphan*/ ) ; 
 scalar_t__ strlen (char const*) ; 

__attribute__((used)) static tree
tinfo_name (tree type)
{
  const char *name;
  tree name_string;

  name = mangle_type_string (type);
  name_string = fix_string_type (build_string (strlen (name) + 1, name));
  return name_string;
}