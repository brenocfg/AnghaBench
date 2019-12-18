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
 int /*<<< orphan*/  LA_EMIT_CHAR (int,struct ui_file*,char) ; 
 int /*<<< orphan*/  fputc_filtered (char,struct ui_file*) ; 

void
c_printchar (int c, struct ui_file *stream)
{
  fputc_filtered ('\'', stream);
  LA_EMIT_CHAR (c, stream, '\'');
  fputc_filtered ('\'', stream);
}