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
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  R_OK ; 
 int /*<<< orphan*/  abort () ; 
 char* find_a_file (int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  read_specs (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  startfile_prefixes ; 

__attribute__((used)) static const char *
include_spec_function (int argc, const char **argv)
{
  char *file;

  if (argc != 1)
    abort ();

  file = find_a_file (&startfile_prefixes, argv[0], R_OK, 0);
  read_specs (file ? file : argv[0], FALSE);

  return NULL;
}