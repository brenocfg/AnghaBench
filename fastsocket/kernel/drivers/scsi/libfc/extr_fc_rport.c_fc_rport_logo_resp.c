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
struct fc_seq {int dummy; } ;
struct fc_lport {int dummy; } ;
struct fc_frame {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  did; } ;

/* Variables and functions */
 int /*<<< orphan*/  FC_RPORT_ID_DBG (struct fc_lport*,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 scalar_t__ IS_ERR (struct fc_frame*) ; 
 int /*<<< orphan*/  fc_els_resp_type (struct fc_frame*) ; 
 int /*<<< orphan*/  fc_frame_free (struct fc_frame*) ; 
 TYPE_1__* fc_seq_exch (struct fc_seq*) ; 

__attribute__((used)) static void fc_rport_logo_resp(struct fc_seq *sp, struct fc_frame *fp,
			       void *lport_arg)
{
	struct fc_lport *lport = lport_arg;

	FC_RPORT_ID_DBG(lport, fc_seq_exch(sp)->did,
			"Received a LOGO %s\n", fc_els_resp_type(fp));
	if (IS_ERR(fp))
		return;
	fc_frame_free(fp);
}