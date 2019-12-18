#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct file_lock {scalar_t__ fl_start; scalar_t__ fl_end; } ;
struct nlm_lock {int /*<<< orphan*/  svid; int /*<<< orphan*/  oh; int /*<<< orphan*/  fh; int /*<<< orphan*/  caller; struct file_lock fl; } ;
typedef  scalar_t__ __s64 ;
typedef  int /*<<< orphan*/  __be32 ;

/* Variables and functions */
 scalar_t__ NLM4_OFFSET_MAX ; 
 scalar_t__ OFFSET_MAX ; 
 int /*<<< orphan*/  htonl (int /*<<< orphan*/ ) ; 
 scalar_t__ loff_t_to_s64 (scalar_t__) ; 
 int /*<<< orphan*/ * nlm4_encode_fh (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * nlm4_encode_oh (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * xdr_encode_hyper (int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/ * xdr_encode_string (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static __be32 *
nlm4_encode_lock(__be32 *p, struct nlm_lock *lock)
{
	struct file_lock	*fl = &lock->fl;
	__s64			start, len;

	if (!(p = xdr_encode_string(p, lock->caller))
	 || !(p = nlm4_encode_fh(p, &lock->fh))
	 || !(p = nlm4_encode_oh(p, &lock->oh)))
		return NULL;

	if (fl->fl_start > NLM4_OFFSET_MAX
	 || (fl->fl_end > NLM4_OFFSET_MAX && fl->fl_end != OFFSET_MAX))
		return NULL;

	*p++ = htonl(lock->svid);

	start = loff_t_to_s64(fl->fl_start);
	if (fl->fl_end == OFFSET_MAX)
		len = 0;
	else
		len = loff_t_to_s64(fl->fl_end - fl->fl_start + 1);

	p = xdr_encode_hyper(p, start);
	p = xdr_encode_hyper(p, len);

	return p;
}