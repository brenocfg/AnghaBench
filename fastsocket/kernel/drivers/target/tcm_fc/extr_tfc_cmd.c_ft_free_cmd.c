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
struct ft_cmd {int /*<<< orphan*/  sess; struct fc_frame* req_frame; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* seq_release ) (scalar_t__) ;} ;
struct fc_lport {TYPE_1__ tt; } ;
struct fc_frame {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  fc_frame_free (struct fc_frame*) ; 
 struct fc_lport* fr_dev (struct fc_frame*) ; 
 scalar_t__ fr_seq (struct fc_frame*) ; 
 int /*<<< orphan*/  ft_sess_put (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct ft_cmd*) ; 
 int /*<<< orphan*/  stub1 (scalar_t__) ; 

__attribute__((used)) static void ft_free_cmd(struct ft_cmd *cmd)
{
	struct fc_frame *fp;
	struct fc_lport *lport;

	if (!cmd)
		return;
	fp = cmd->req_frame;
	lport = fr_dev(fp);
	if (fr_seq(fp))
		lport->tt.seq_release(fr_seq(fp));
	fc_frame_free(fp);
	ft_sess_put(cmd->sess);	/* undo get from lookup at recv */
	kfree(cmd);
}