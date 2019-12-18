#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u64 ;
struct salinfo_data {int /*<<< orphan*/  type; scalar_t__ log_buffer; int /*<<< orphan*/  log_size; } ;
struct TYPE_2__ {scalar_t__ severity; } ;
typedef  TYPE_1__ sal_log_record_header_t ;

/* Variables and functions */
 int /*<<< orphan*/  ia64_sal_clear_state_info (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ia64_sal_get_state_info (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ sal_log_severity_corrected ; 

__attribute__((used)) static void
salinfo_log_read_cpu(void *context)
{
	struct salinfo_data *data = context;
	sal_log_record_header_t *rh;
	data->log_size = ia64_sal_get_state_info(data->type, (u64 *) data->log_buffer);
	rh = (sal_log_record_header_t *)(data->log_buffer);
	/* Clear corrected errors as they are read from SAL */
	if (rh->severity == sal_log_severity_corrected)
		ia64_sal_clear_state_info(data->type);
}