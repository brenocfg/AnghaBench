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
struct pevent_record {int /*<<< orphan*/  data; } ;
struct pevent {int dummy; } ;

/* Variables and functions */
 int trace_parse_common_type (struct pevent*,int /*<<< orphan*/ ) ; 

int pevent_data_type(struct pevent *pevent, struct pevent_record *rec)
{
	return trace_parse_common_type(pevent, rec->data);
}