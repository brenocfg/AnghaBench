#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {scalar_t__ state; } ;
typedef  TYPE_1__ network_mysqld_com_query_result_t ;
typedef  int /*<<< orphan*/  gboolean ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 scalar_t__ PARSE_COM_QUERY_LOCAL_INFILE_DATA ; 
 int /*<<< orphan*/  TRUE ; 

gboolean network_mysqld_com_query_result_is_local_infile(network_mysqld_com_query_result_t *udata) {
	return (udata->state == PARSE_COM_QUERY_LOCAL_INFILE_DATA) ? TRUE : FALSE;
}