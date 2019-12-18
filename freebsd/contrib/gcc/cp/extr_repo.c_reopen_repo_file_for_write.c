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
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int /*<<< orphan*/  error (char*,int /*<<< orphan*/ ) ; 
 scalar_t__ flag_use_repository ; 
 int /*<<< orphan*/ * fopen (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  repo_name ; 

__attribute__((used)) static FILE *
reopen_repo_file_for_write (void)
{
  FILE *repo_file = fopen (repo_name, "w");

  if (repo_file == 0)
    {
      error ("can't create repository information file %qs", repo_name);
      flag_use_repository = 0;
    }

  return repo_file;
}