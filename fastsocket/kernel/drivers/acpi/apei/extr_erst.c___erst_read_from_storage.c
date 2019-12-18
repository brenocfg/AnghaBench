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
typedef  scalar_t__ u64 ;
struct apei_exec_context {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ACPI_ERST_BEGIN_READ ; 
 int /*<<< orphan*/  ACPI_ERST_CHECK_BUSY_STATUS ; 
 int /*<<< orphan*/  ACPI_ERST_END ; 
 int /*<<< orphan*/  ACPI_ERST_EXECUTE_OPERATION ; 
 int /*<<< orphan*/  ACPI_ERST_GET_COMMAND_STATUS ; 
 int /*<<< orphan*/  ACPI_ERST_SET_RECORD_ID ; 
 int /*<<< orphan*/  ACPI_ERST_SET_RECORD_OFFSET ; 
 int EIO ; 
 scalar_t__ FIRMWARE_TIMEOUT ; 
 int /*<<< orphan*/  SPIN_UNIT ; 
 scalar_t__ apei_exec_ctx_get_output (struct apei_exec_context*) ; 
 int /*<<< orphan*/  apei_exec_ctx_set_input (struct apei_exec_context*,scalar_t__) ; 
 int apei_exec_run (struct apei_exec_context*,int /*<<< orphan*/ ) ; 
 int apei_exec_run_optional (struct apei_exec_context*,int /*<<< orphan*/ ) ; 
 int erst_errno (scalar_t__) ; 
 int /*<<< orphan*/  erst_exec_ctx_init (struct apei_exec_context*) ; 
 scalar_t__ erst_timedout (scalar_t__*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int __erst_read_from_storage(u64 record_id, u64 offset)
{
	struct apei_exec_context ctx;
	u64 timeout = FIRMWARE_TIMEOUT;
	u64 val;
	int rc;

	erst_exec_ctx_init(&ctx);
	rc = apei_exec_run_optional(&ctx, ACPI_ERST_BEGIN_READ);
	if (rc)
		return rc;
	apei_exec_ctx_set_input(&ctx, offset);
	rc = apei_exec_run(&ctx, ACPI_ERST_SET_RECORD_OFFSET);
	if (rc)
		return rc;
	apei_exec_ctx_set_input(&ctx, record_id);
	rc = apei_exec_run(&ctx, ACPI_ERST_SET_RECORD_ID);
	if (rc)
		return rc;
	rc = apei_exec_run(&ctx, ACPI_ERST_EXECUTE_OPERATION);
	if (rc)
		return rc;
	for (;;) {
		rc = apei_exec_run(&ctx, ACPI_ERST_CHECK_BUSY_STATUS);
		if (rc)
			return rc;
		val = apei_exec_ctx_get_output(&ctx);
		if (!val)
			break;
		if (erst_timedout(&timeout, SPIN_UNIT))
			return -EIO;
	};
	rc = apei_exec_run(&ctx, ACPI_ERST_GET_COMMAND_STATUS);
	if (rc)
		return rc;
	val = apei_exec_ctx_get_output(&ctx);
	rc = apei_exec_run_optional(&ctx, ACPI_ERST_END);
	if (rc)
		return rc;

	return erst_errno(val);
}