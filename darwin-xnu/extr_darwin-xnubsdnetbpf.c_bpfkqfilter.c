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
struct knote {scalar_t__ kn_filter; int /*<<< orphan*/  kn_filtid; struct bpf_d* kn_hook; int /*<<< orphan*/  kn_data; void* kn_flags; } ;
struct TYPE_2__ {int /*<<< orphan*/  si_note; } ;
struct bpf_d {int bd_flags; TYPE_1__ bd_sel; int /*<<< orphan*/ * bd_bif; } ;
typedef  int /*<<< orphan*/  dev_t ;

/* Variables and functions */
 int BPF_CLOSING ; 
 struct bpf_d* BPF_DEV_RESERVED ; 
 int BPF_KNOTE ; 
 scalar_t__ CDEV_MAJOR ; 
 int /*<<< orphan*/  EINVAL ; 
 int /*<<< orphan*/  ENXIO ; 
 int /*<<< orphan*/  EVFILTID_BPFREAD ; 
 scalar_t__ EVFILT_READ ; 
 void* EV_ERROR ; 
 int /*<<< orphan*/  KNOTE_ATTACH (int /*<<< orphan*/ *,struct knote*) ; 
 struct bpf_d** bpf_dtab ; 
 int /*<<< orphan*/  bpf_mlock ; 
 int filt_bpfread_common (struct knote*,struct bpf_d*) ; 
 int /*<<< orphan*/  lck_mtx_lock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lck_mtx_unlock (int /*<<< orphan*/ ) ; 
 scalar_t__ major (int /*<<< orphan*/ ) ; 
 size_t minor (int /*<<< orphan*/ ) ; 

int
bpfkqfilter(dev_t dev, struct knote *kn)
{
	struct bpf_d *d;
	int res;

	/*
	 * Is this device a bpf?
	 */
	if (major(dev) != CDEV_MAJOR ||
	    kn->kn_filter != EVFILT_READ) {
		kn->kn_flags = EV_ERROR;
		kn->kn_data = EINVAL;
		return (0);
	}

	lck_mtx_lock(bpf_mlock);

	d = bpf_dtab[minor(dev)];

	if (d == NULL || d == BPF_DEV_RESERVED ||
	    (d->bd_flags & BPF_CLOSING) != 0 ||
	    d->bd_bif == NULL) {
		lck_mtx_unlock(bpf_mlock);
		kn->kn_flags = EV_ERROR;
		kn->kn_data = ENXIO;
		return (0);
	}

	kn->kn_hook = d;
	kn->kn_filtid = EVFILTID_BPFREAD;
	KNOTE_ATTACH(&d->bd_sel.si_note, kn);
	d->bd_flags |= BPF_KNOTE;

	/* capture the current state */
	res = filt_bpfread_common(kn, d);

	lck_mtx_unlock(bpf_mlock);

	return (res);
}