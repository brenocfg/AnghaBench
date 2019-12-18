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

/* Variables and functions */
 int /*<<< orphan*/  R_OK ; 
 char* find_a_file (int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  startfile_prefixes ; 

__attribute__((used)) static const char *
find_file (const char *name)
{
  char *newname = find_a_file (&startfile_prefixes, name, R_OK, true);
  return newname ? newname : name;
}