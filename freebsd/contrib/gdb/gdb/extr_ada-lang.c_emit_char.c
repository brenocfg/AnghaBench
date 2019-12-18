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
 int /*<<< orphan*/  ada_emit_char (int,struct ui_file*,int,int) ; 

__attribute__((used)) static void
emit_char (int c, struct ui_file *stream, int quoter)
{
  ada_emit_char (c, stream, quoter, 1);
}