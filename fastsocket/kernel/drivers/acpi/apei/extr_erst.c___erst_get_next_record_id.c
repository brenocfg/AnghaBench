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
typedef  int /*<<< orphan*/  u64 ;
struct apei_exec_context {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ACPI_ERST_GET_RECORD_ID ; 
 int /*<<< orphan*/  apei_exec_ctx_get_output (struct apei_exec_context*) ; 
 int apei_exec_run (struct apei_exec_context*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  erst_exec_ctx_init (struct apei_exec_context*) ; 

__attribute__((used)) static int __erst_get_next_record_id(u64 *record_id)
{
	struct apei_exec_context ctx;
	int rc;

	erst_exec_ctx_init(&ctx);
	rc = apei_exec_run(&ctx, ACPI_ERST_GET_RECORD_ID);
	if (rc)
		return rc;
	*record_id = apei_exec_ctx_get_output(&ctx);

	return 0;
}