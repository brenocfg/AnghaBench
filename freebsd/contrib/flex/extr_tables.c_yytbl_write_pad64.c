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
struct yytbl_writer {int /*<<< orphan*/  total_written; } ;

/* Variables and functions */
 int yypad64 (int /*<<< orphan*/ ) ; 
 scalar_t__ yytbl_write8 (struct yytbl_writer*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int yytbl_write_pad64 (struct yytbl_writer *wr)
{
	int     pad, bwritten = 0;

	pad = yypad64 (wr->total_written);
	while (pad-- > 0)
		if (yytbl_write8 (wr, 0) < 0)
			return -1;
		else
			bwritten++;
	return bwritten;
}