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
struct TYPE_3__ {int target; } ;
struct TYPE_4__ {scalar_t__ rspcode; TYPE_1__ servparams; } ;
struct fc_prli_s {scalar_t__ command; TYPE_2__ parampage; } ;
typedef  enum fc_parse_status { ____Placeholder_fc_parse_status } fc_parse_status ;

/* Variables and functions */
 scalar_t__ FC_ELS_ACC ; 
 int FC_PARSE_FAILURE ; 
 int FC_PARSE_OK ; 
 scalar_t__ FC_PRLI_ACC_PREDEF_IMG ; 
 scalar_t__ FC_PRLI_ACC_XQTD ; 

enum fc_parse_status
fc_prli_rsp_parse(struct fc_prli_s *prli, int len)
{
	if (len < sizeof(struct fc_prli_s))
		return FC_PARSE_FAILURE;

	if (prli->command != FC_ELS_ACC)
		return FC_PARSE_FAILURE;

	if ((prli->parampage.rspcode != FC_PRLI_ACC_XQTD)
	    && (prli->parampage.rspcode != FC_PRLI_ACC_PREDEF_IMG))
		return FC_PARSE_FAILURE;

	if (prli->parampage.servparams.target != 1)
		return FC_PARSE_FAILURE;

	return FC_PARSE_OK;
}