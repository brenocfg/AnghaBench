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
struct yytbl_writer {scalar_t__ total_written; int /*<<< orphan*/ * out; } ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */

int yytbl_writer_init (struct yytbl_writer *wr, FILE * out)
{
	wr->out = out;
	wr->total_written = 0;
	return 0;
}