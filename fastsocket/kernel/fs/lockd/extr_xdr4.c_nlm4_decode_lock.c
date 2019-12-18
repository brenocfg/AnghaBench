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
struct file_lock {void* fl_end; void* fl_start; int /*<<< orphan*/  fl_type; int /*<<< orphan*/  fl_flags; scalar_t__ fl_pid; int /*<<< orphan*/  fl_owner; } ;
struct nlm_lock {scalar_t__ svid; int /*<<< orphan*/  oh; int /*<<< orphan*/  fh; int /*<<< orphan*/  len; int /*<<< orphan*/  caller; struct file_lock fl; } ;
typedef  scalar_t__ pid_t ;
typedef  scalar_t__ __u64 ;
typedef  scalar_t__ __s64 ;
typedef  int /*<<< orphan*/  __be32 ;
struct TYPE_2__ {int /*<<< orphan*/  files; } ;

/* Variables and functions */
 int /*<<< orphan*/  FL_POSIX ; 
 int /*<<< orphan*/  F_RDLCK ; 
 int /*<<< orphan*/  NLM_MAXSTRLEN ; 
 void* OFFSET_MAX ; 
 TYPE_1__* current ; 
 int /*<<< orphan*/  locks_init_lock (struct file_lock*) ; 
 int /*<<< orphan*/ * nlm4_decode_fh (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * nlm4_decode_oh (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ ntohl (int /*<<< orphan*/ ) ; 
 void* s64_to_loff_t (scalar_t__) ; 
 int /*<<< orphan*/ * xdr_decode_hyper (int /*<<< orphan*/ *,scalar_t__*) ; 
 int /*<<< orphan*/ * xdr_decode_string_inplace (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static __be32 *
nlm4_decode_lock(__be32 *p, struct nlm_lock *lock)
{
	struct file_lock	*fl = &lock->fl;
	__u64			len, start;
	__s64			end;

	if (!(p = xdr_decode_string_inplace(p, &lock->caller,
					    &lock->len, NLM_MAXSTRLEN))
	 || !(p = nlm4_decode_fh(p, &lock->fh))
	 || !(p = nlm4_decode_oh(p, &lock->oh)))
		return NULL;
	lock->svid  = ntohl(*p++);

	locks_init_lock(fl);
	fl->fl_owner = current->files;
	fl->fl_pid   = (pid_t)lock->svid;
	fl->fl_flags = FL_POSIX;
	fl->fl_type  = F_RDLCK;		/* as good as anything else */
	p = xdr_decode_hyper(p, &start);
	p = xdr_decode_hyper(p, &len);
	end = start + len - 1;

	fl->fl_start = s64_to_loff_t(start);

	if (len == 0 || end < 0)
		fl->fl_end = OFFSET_MAX;
	else
		fl->fl_end = s64_to_loff_t(end);
	return p;
}