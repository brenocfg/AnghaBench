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
 int /*<<< orphan*/ * fopen (char*,char const*) ; 
 int /*<<< orphan*/  make_cleanup_fclose (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  perror_with_name (char*) ; 

FILE *
fopen_with_cleanup (char *filename, const char *mode)
{
  FILE *file = fopen (filename, mode);
  if (file == NULL)
    perror_with_name (filename);
  make_cleanup_fclose (file);
  return file;
}