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
 int /*<<< orphan*/  fail (char*) ; 
 int /*<<< orphan*/  read_derived (char*) ; 
 int /*<<< orphan*/  read_table (char*) ; 
 int /*<<< orphan*/  read_ucnid (char*) ; 
 int /*<<< orphan*/  write_copyright () ; 
 int /*<<< orphan*/  write_table () ; 

int
main(int argc, char ** argv)
{
  if (argc != 4)
    fail ("too few arguments to makeucn");
  read_ucnid (argv[1]);
  read_table (argv[2]);
  read_derived (argv[3]);

  write_copyright ();
  write_table ();
  return 0;
}