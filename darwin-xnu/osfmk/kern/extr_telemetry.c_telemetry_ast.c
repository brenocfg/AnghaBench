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
typedef  int uint8_t ;
typedef  int /*<<< orphan*/  thread_t ;
typedef  int ast_t ;

/* Variables and functions */
 int AST_TELEMETRY_ALL ; 
 int AST_TELEMETRY_IO ; 
 int AST_TELEMETRY_KERNEL ; 
 int AST_TELEMETRY_PMI ; 
 int AST_TELEMETRY_USER ; 
 int /*<<< orphan*/  assert (int) ; 
 int kIORecord ; 
 int kInterruptRecord ; 
 int kPMIRecord ; 
 int kUserMode ; 
 int /*<<< orphan*/  telemetry_buffer ; 
 int /*<<< orphan*/  telemetry_take_sample (int /*<<< orphan*/ ,int,int /*<<< orphan*/ *) ; 

void telemetry_ast(thread_t thread, ast_t reasons)
{
	assert((reasons & AST_TELEMETRY_ALL) != 0);

	uint8_t record_type = 0;
	if (reasons & AST_TELEMETRY_IO) {
		record_type |= kIORecord;
	}
	if (reasons & (AST_TELEMETRY_USER | AST_TELEMETRY_KERNEL)) {
		record_type |= (reasons & AST_TELEMETRY_PMI) ? kPMIRecord :
				kInterruptRecord;
	}

	uint8_t user_telemetry = (reasons & AST_TELEMETRY_USER) ? kUserMode : 0;

	uint8_t microsnapshot_flags = record_type | user_telemetry;

	telemetry_take_sample(thread, microsnapshot_flags, &telemetry_buffer);
}