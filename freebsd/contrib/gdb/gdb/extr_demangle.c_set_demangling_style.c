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
 int /*<<< orphan*/ * current_demangling_style_string ; 
 int /*<<< orphan*/ * savestring (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_demangling_command (char*,int /*<<< orphan*/ ,struct cmd_list_element*) ; 
 int /*<<< orphan*/  strlen (char*) ; 
 int /*<<< orphan*/  xfree (int /*<<< orphan*/ *) ; 

void
set_demangling_style (char *style)
{
  if (current_demangling_style_string != NULL)
    {
      xfree (current_demangling_style_string);
    }
  current_demangling_style_string = savestring (style, strlen (style));
  set_demangling_command ((char *) NULL, 0, (struct cmd_list_element *) NULL);
}