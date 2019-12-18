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
struct header_file {int instance; int /*<<< orphan*/  name; } ;

/* Variables and functions */
 struct header_file* HEADER_FILES (int /*<<< orphan*/ ) ; 
 int N_HEADER_FILES (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  add_this_object_header_file (int) ; 
 int /*<<< orphan*/  current_objfile ; 
 int /*<<< orphan*/  repeated_header_complaint (char*,int /*<<< orphan*/ ) ; 
 scalar_t__ strcmp (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  symnum ; 

__attribute__((used)) static void
add_old_header_file (char *name, int instance)
{
  struct header_file *p = HEADER_FILES (current_objfile);
  int i;

  for (i = 0; i < N_HEADER_FILES (current_objfile); i++)
    if (strcmp (p[i].name, name) == 0 && instance == p[i].instance)
      {
	add_this_object_header_file (i);
	return;
      }
  repeated_header_complaint (name, symnum);
}