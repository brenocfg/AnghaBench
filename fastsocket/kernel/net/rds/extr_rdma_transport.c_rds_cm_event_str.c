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
typedef  enum rdma_cm_event_type { ____Placeholder_rdma_cm_event_type } rdma_cm_event_type ;

/* Variables and functions */
 int /*<<< orphan*/  ARRAY_SIZE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rds_cm_event_strings ; 
 char* rds_str_array (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static char *rds_cm_event_str(enum rdma_cm_event_type type)
{
	return rds_str_array(rds_cm_event_strings,
			     ARRAY_SIZE(rds_cm_event_strings), type);
}