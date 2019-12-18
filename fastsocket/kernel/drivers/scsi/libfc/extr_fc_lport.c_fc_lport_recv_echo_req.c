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
struct TYPE_2__ {int /*<<< orphan*/  (* frame_send ) (struct fc_lport*,struct fc_frame*) ;} ;
struct fc_lport {TYPE_1__ tt; } ;
struct fc_frame_header {int dummy; } ;
struct fc_frame {int dummy; } ;
typedef  int /*<<< orphan*/  __be32 ;

/* Variables and functions */
 int ELS_LS_ACC ; 
 int /*<<< orphan*/  FC_LPORT_DBG (struct fc_lport*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FC_RCTL_ELS_REP ; 
 int /*<<< orphan*/  fc_fill_reply_hdr (struct fc_frame*,struct fc_frame*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct fc_frame* fc_frame_alloc (struct fc_lport*,unsigned int) ; 
 int /*<<< orphan*/  fc_frame_free (struct fc_frame*) ; 
 void* fc_frame_payload_get (struct fc_frame*,unsigned int) ; 
 int /*<<< orphan*/  fc_lport_state (struct fc_lport*) ; 
 int fr_len (struct fc_frame*) ; 
 int /*<<< orphan*/  htonl (int) ; 
 int /*<<< orphan*/  memcpy (void*,void*,unsigned int) ; 
 int /*<<< orphan*/  stub1 (struct fc_lport*,struct fc_frame*) ; 

__attribute__((used)) static void fc_lport_recv_echo_req(struct fc_lport *lport,
				   struct fc_frame *in_fp)
{
	struct fc_frame *fp;
	unsigned int len;
	void *pp;
	void *dp;

	FC_LPORT_DBG(lport, "Received ECHO request while in state %s\n",
		     fc_lport_state(lport));

	len = fr_len(in_fp) - sizeof(struct fc_frame_header);
	pp = fc_frame_payload_get(in_fp, len);

	if (len < sizeof(__be32))
		len = sizeof(__be32);

	fp = fc_frame_alloc(lport, len);
	if (fp) {
		dp = fc_frame_payload_get(fp, len);
		memcpy(dp, pp, len);
		*((__be32 *)dp) = htonl(ELS_LS_ACC << 24);
		fc_fill_reply_hdr(fp, in_fp, FC_RCTL_ELS_REP, 0);
		lport->tt.frame_send(lport, fp);
	}
	fc_frame_free(in_fp);
}