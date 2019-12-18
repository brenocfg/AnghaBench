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
struct file_lock {scalar_t__ fl_type; scalar_t__ fl_start; scalar_t__ fl_end; } ;
struct TYPE_2__ {int /*<<< orphan*/  oh; int /*<<< orphan*/  svid; struct file_lock fl; } ;
struct nlm_res {scalar_t__ status; TYPE_1__ lock; int /*<<< orphan*/  cookie; } ;
typedef  int /*<<< orphan*/  s32 ;
typedef  int /*<<< orphan*/  __be32 ;

/* Variables and functions */
 scalar_t__ F_RDLCK ; 
 scalar_t__ OFFSET_MAX ; 
 void* htonl (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  loff_t_to_s32 (scalar_t__) ; 
 int /*<<< orphan*/ * nlm_encode_cookie (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ nlm_lck_denied ; 
 int /*<<< orphan*/ * xdr_encode_netobj (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  xdr_one ; 
 int /*<<< orphan*/  xdr_zero ; 

__attribute__((used)) static __be32 *
nlm_encode_testres(__be32 *p, struct nlm_res *resp)
{
	s32		start, len;

	if (!(p = nlm_encode_cookie(p, &resp->cookie)))
		return NULL;
	*p++ = resp->status;

	if (resp->status == nlm_lck_denied) {
		struct file_lock	*fl = &resp->lock.fl;

		*p++ = (fl->fl_type == F_RDLCK)? xdr_zero : xdr_one;
		*p++ = htonl(resp->lock.svid);

		/* Encode owner handle. */
		if (!(p = xdr_encode_netobj(p, &resp->lock.oh)))
			return NULL;

		start = loff_t_to_s32(fl->fl_start);
		if (fl->fl_end == OFFSET_MAX)
			len = 0;
		else
			len = loff_t_to_s32(fl->fl_end - fl->fl_start + 1);

		*p++ = htonl(start);
		*p++ = htonl(len);
	}

	return p;
}