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
struct si_sm_data {int* read_data; int* write_data; int read_count; } ;

/* Variables and functions */

__attribute__((used)) static void force_result(struct si_sm_data *bt, unsigned char completion_code)
{
	bt->read_data[0] = 4;				/* # following bytes */
	bt->read_data[1] = bt->write_data[1] | 4;	/* Odd NetFn/LUN */
	bt->read_data[2] = bt->write_data[2];		/* seq (ignored) */
	bt->read_data[3] = bt->write_data[3];		/* Command */
	bt->read_data[4] = completion_code;
	bt->read_count = 5;
}