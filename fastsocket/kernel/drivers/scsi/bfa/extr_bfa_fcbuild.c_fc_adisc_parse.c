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
typedef  int /*<<< orphan*/  wwn_t ;
typedef  scalar_t__ u32 ;
struct fchs_s {int dummy; } ;
struct TYPE_2__ {scalar_t__ els_code; } ;
struct fc_adisc_s {scalar_t__ nport_id; int /*<<< orphan*/  orig_node_name; int /*<<< orphan*/  orig_port_name; TYPE_1__ els_cmd; } ;
typedef  enum fc_parse_status { ____Placeholder_fc_parse_status } fc_parse_status ;

/* Variables and functions */
 scalar_t__ FC_ELS_ACC ; 
 int FC_PARSE_FAILURE ; 
 int FC_PARSE_OK ; 
 scalar_t__ wwn_is_equal (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

enum fc_parse_status
fc_adisc_parse(struct fchs_s *fchs, void *pld, u32 host_dap, wwn_t node_name,
	       wwn_t port_name)
{
	struct fc_adisc_s *adisc = (struct fc_adisc_s *) pld;

	if (adisc->els_cmd.els_code != FC_ELS_ACC)
		return FC_PARSE_FAILURE;

	if ((adisc->nport_id == (host_dap))
	    && wwn_is_equal(adisc->orig_port_name, port_name)
	    && wwn_is_equal(adisc->orig_node_name, node_name))
		return FC_PARSE_OK;

	return FC_PARSE_FAILURE;
}