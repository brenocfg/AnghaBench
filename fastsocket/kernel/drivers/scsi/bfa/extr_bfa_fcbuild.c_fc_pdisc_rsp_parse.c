#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  wwn_t ;
typedef  int /*<<< orphan*/  u16 ;
struct fchs_s {int dummy; } ;
struct TYPE_4__ {int /*<<< orphan*/  rxsz; int /*<<< orphan*/  class_valid; } ;
struct TYPE_3__ {scalar_t__ els_code; } ;
struct fc_logi_s {TYPE_2__ class3; int /*<<< orphan*/  port_name; TYPE_1__ els_cmd; } ;

/* Variables and functions */
 scalar_t__ FC_ELS_ACC ; 
 scalar_t__ FC_MIN_PDUSZ ; 
 int /*<<< orphan*/  FC_PARSE_ACC_INVAL ; 
 int /*<<< orphan*/  FC_PARSE_LEN_INVAL ; 
 int /*<<< orphan*/  FC_PARSE_NWWN_NOT_EQUAL ; 
 int /*<<< orphan*/  FC_PARSE_OK ; 
 int /*<<< orphan*/  FC_PARSE_PWWN_NOT_EQUAL ; 
 int /*<<< orphan*/  FC_PARSE_RXSZ_INVAL ; 
 scalar_t__ be16_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wwn_is_equal (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

u16
fc_pdisc_rsp_parse(struct fchs_s *fchs, int len, wwn_t port_name)
{
	struct fc_logi_s *pdisc = (struct fc_logi_s *) (fchs + 1);

	if (len < sizeof(struct fc_logi_s))
		return FC_PARSE_LEN_INVAL;

	if (pdisc->els_cmd.els_code != FC_ELS_ACC)
		return FC_PARSE_ACC_INVAL;

	if (!wwn_is_equal(pdisc->port_name, port_name))
		return FC_PARSE_PWWN_NOT_EQUAL;

	if (!pdisc->class3.class_valid)
		return FC_PARSE_NWWN_NOT_EQUAL;

	if (be16_to_cpu(pdisc->class3.rxsz) < (FC_MIN_PDUSZ))
		return FC_PARSE_RXSZ_INVAL;

	return FC_PARSE_OK;
}