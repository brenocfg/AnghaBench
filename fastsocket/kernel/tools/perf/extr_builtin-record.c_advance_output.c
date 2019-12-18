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
struct perf_record {size_t bytes_written; } ;

/* Variables and functions */

__attribute__((used)) static void advance_output(struct perf_record *rec, size_t size)
{
	rec->bytes_written += size;
}