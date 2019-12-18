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
struct c_fileinfo {int time; } ;

/* Variables and functions */
 int body_time ; 
 int /*<<< orphan*/  dump_one_header ; 
 int /*<<< orphan*/  file_info_tree ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,...) ; 
 struct c_fileinfo* get_fileinfo (int /*<<< orphan*/ ) ; 
 int get_run_time () ; 
 int header_time ; 
 int /*<<< orphan*/  input_filename ; 
 int /*<<< orphan*/  print_time (char*,int) ; 
 int /*<<< orphan*/  splay_tree_foreach (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stderr ; 

void
dump_time_statistics (void)
{
  struct c_fileinfo *file = get_fileinfo (input_filename);
  int this_time = get_run_time ();
  file->time += this_time - body_time;

  fprintf (stderr, "\n******\n");
  print_time ("header files (total)", header_time);
  print_time ("main file (total)", this_time - body_time);
  fprintf (stderr, "ratio = %g : 1\n",
	   (double) header_time / (double) (this_time - body_time));
  fprintf (stderr, "\n******\n");

  splay_tree_foreach (file_info_tree, dump_one_header, 0);
}