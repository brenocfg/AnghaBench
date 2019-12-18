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
 int /*<<< orphan*/ * fopen_with_cleanup (char*,char*) ; 
 int fwrite (char*,int,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  perror_with_name (char*) ; 

__attribute__((used)) static void
dump_binary_file (char *filename, char *mode, 
		  char *buf, int len)
{
  FILE *file;
  int status;

  file = fopen_with_cleanup (filename, mode);
  status = fwrite (buf, len, 1, file);
  if (status != 1)
    perror_with_name (filename);
}