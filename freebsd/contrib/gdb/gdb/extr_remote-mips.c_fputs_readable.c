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
 int /*<<< orphan*/  fputc_readable (int,struct ui_file*) ; 

__attribute__((used)) static void
fputs_readable (const char *string, struct ui_file *file)
{
  int c;

  while ((c = *string++) != '\0')
    fputc_readable (c, file);
}