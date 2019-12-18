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
struct yytbl_writer {int total_written; int /*<<< orphan*/  out; } ;
typedef  int flex_int32_t ;

/* Variables and functions */
 int fwrite (void*,int,int,int /*<<< orphan*/ ) ; 

int yytbl_writen (struct yytbl_writer *wr, void *v, flex_int32_t len)
{
	int  rv;

	rv = fwrite (v, 1, len, wr->out);
	if (rv != len)
		return -1;
	wr->total_written += len;
	return len;
}