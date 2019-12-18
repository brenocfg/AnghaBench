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
struct ui_file {int dummy; } ;
struct symbol {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  fprintf_filtered (struct ui_file*,char*) ; 

__attribute__((used)) static int
loclist_describe_location (struct symbol *symbol, struct ui_file *stream)
{
  /* FIXME: Could print the entire list of locations.  */
  fprintf_filtered (stream, "a variable with multiple locations");
  return 1;
}