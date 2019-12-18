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
struct bi_record {unsigned long* data; int tag; } ;

/* Variables and functions */
#define  BI_APOLLO_MODEL 128 
 unsigned long apollo_model ; 

int apollo_parse_bootinfo(const struct bi_record *record) {

	int unknown = 0;
	const unsigned long *data = record->data;

	switch(record->tag) {
		case BI_APOLLO_MODEL:
			apollo_model=*data;
			break;

		default:
			 unknown=1;
	}

	return unknown;
}