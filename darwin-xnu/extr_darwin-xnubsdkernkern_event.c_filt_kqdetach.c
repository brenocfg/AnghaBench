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
struct kqueue {int dummy; } ;
struct TYPE_4__ {int /*<<< orphan*/  si_note; } ;
struct kqfile {TYPE_2__ kqf_sel; struct kqueue kqf_kqueue; } ;
struct knote {TYPE_1__* kn_fp; } ;
struct TYPE_3__ {scalar_t__ f_data; } ;

/* Variables and functions */
 int /*<<< orphan*/  KNOTE_DETACH (int /*<<< orphan*/ *,struct knote*) ; 
 int /*<<< orphan*/  kqlock (struct kqueue*) ; 
 int /*<<< orphan*/  kqunlock (struct kqueue*) ; 

__attribute__((used)) static void
filt_kqdetach(struct knote *kn)
{
	struct kqfile *kqf = (struct kqfile *)kn->kn_fp->f_data;
	struct kqueue *kq = &kqf->kqf_kqueue;

	kqlock(kq);
	KNOTE_DETACH(&kqf->kqf_sel.si_note, kn);
	kqunlock(kq);
}