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
typedef  void* u32 ;
struct rpc_rqst {int dummy; } ;
struct file_lock {void* fl_end; void* fl_start; int /*<<< orphan*/  fl_type; int /*<<< orphan*/  fl_flags; scalar_t__ fl_pid; } ;
struct TYPE_2__ {int /*<<< orphan*/  oh; void* svid; struct file_lock fl; } ;
struct nlm_res {scalar_t__ status; TYPE_1__ lock; int /*<<< orphan*/  cookie; } ;
typedef  scalar_t__ s32 ;
typedef  scalar_t__ pid_t ;
typedef  int /*<<< orphan*/  __be32 ;

/* Variables and functions */
 int EIO ; 
 int /*<<< orphan*/  FL_POSIX ; 
 int /*<<< orphan*/  F_RDLCK ; 
 int /*<<< orphan*/  F_WRLCK ; 
 void* OFFSET_MAX ; 
 int /*<<< orphan*/  locks_init_lock (struct file_lock*) ; 
 int /*<<< orphan*/  memset (TYPE_1__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/ * nlm_decode_cookie (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * nlm_decode_oh (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ nlm_lck_denied ; 
 void* ntohl (int /*<<< orphan*/ ) ; 
 void* s32_to_loff_t (scalar_t__) ; 

__attribute__((used)) static int
nlmclt_decode_testres(struct rpc_rqst *req, __be32 *p, struct nlm_res *resp)
{
	if (!(p = nlm_decode_cookie(p, &resp->cookie)))
		return -EIO;
	resp->status = *p++;
	if (resp->status == nlm_lck_denied) {
		struct file_lock	*fl = &resp->lock.fl;
		u32			excl;
		s32			start, len, end;

		memset(&resp->lock, 0, sizeof(resp->lock));
		locks_init_lock(fl);
		excl = ntohl(*p++);
		resp->lock.svid = ntohl(*p++);
		fl->fl_pid = (pid_t)resp->lock.svid;
		if (!(p = nlm_decode_oh(p, &resp->lock.oh)))
			return -EIO;

		fl->fl_flags = FL_POSIX;
		fl->fl_type  = excl? F_WRLCK : F_RDLCK;
		start = ntohl(*p++);
		len = ntohl(*p++);
		end = start + len - 1;

		fl->fl_start = s32_to_loff_t(start);
		if (len == 0 || end < 0)
			fl->fl_end = OFFSET_MAX;
		else
			fl->fl_end = s32_to_loff_t(end);
	}
	return 0;
}