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
struct cmd_list_element {int dummy; } ;

/* Variables and functions */
 struct cmd_list_element* add_cmd (char*,int /*<<< orphan*/ ,void (*) (char*,int),char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  infolist ; 
 int /*<<< orphan*/  no_class ; 

struct cmd_list_element *
add_info (char *name, void (*fun) (char *, int), char *doc)
{
  return add_cmd (name, no_class, fun, doc, &infolist);
}