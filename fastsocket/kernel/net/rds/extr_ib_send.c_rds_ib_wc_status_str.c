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
typedef  enum ib_wc_status { ____Placeholder_ib_wc_status } ib_wc_status ;

/* Variables and functions */
 int /*<<< orphan*/  ARRAY_SIZE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rds_ib_wc_status_strings ; 
 char* rds_str_array (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

char *rds_ib_wc_status_str(enum ib_wc_status status)
{
	return rds_str_array(rds_ib_wc_status_strings,
			     ARRAY_SIZE(rds_ib_wc_status_strings), status);
}