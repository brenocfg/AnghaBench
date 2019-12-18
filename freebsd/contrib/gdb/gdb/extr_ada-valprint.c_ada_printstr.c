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

/* Variables and functions */
 int /*<<< orphan*/  printstr (struct ui_file*,char*,unsigned int,int,int) ; 

void
ada_printstr (struct ui_file *stream, char *string, unsigned int length,
	      int force_ellipses, int width)
{
  printstr (stream, string, length, force_ellipses, width);
}