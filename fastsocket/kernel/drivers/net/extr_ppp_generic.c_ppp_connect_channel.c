#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct ppp_net {int /*<<< orphan*/  all_ppp_mutex; } ;
struct TYPE_6__ {scalar_t__ hdrlen; int /*<<< orphan*/  refcnt; } ;
struct ppp {TYPE_3__ file; int /*<<< orphan*/  n_channels; int /*<<< orphan*/  channels; TYPE_2__* dev; } ;
struct TYPE_4__ {scalar_t__ hdrlen; } ;
struct channel {int /*<<< orphan*/  upl; struct ppp* ppp; int /*<<< orphan*/  clist; TYPE_1__ file; int /*<<< orphan*/  chan_net; } ;
struct TYPE_5__ {int hard_header_len; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENXIO ; 
 int /*<<< orphan*/  atomic_inc (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 struct ppp* ppp_find_unit (struct ppp_net*,int) ; 
 int /*<<< orphan*/  ppp_lock (struct ppp*) ; 
 struct ppp_net* ppp_pernet (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ppp_unlock (struct ppp*) ; 
 int /*<<< orphan*/  write_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  write_unlock_bh (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
ppp_connect_channel(struct channel *pch, int unit)
{
	struct ppp *ppp;
	struct ppp_net *pn;
	int ret = -ENXIO;
	int hdrlen;

	pn = ppp_pernet(pch->chan_net);

	mutex_lock(&pn->all_ppp_mutex);
	ppp = ppp_find_unit(pn, unit);
	if (!ppp)
		goto out;
	write_lock_bh(&pch->upl);
	ret = -EINVAL;
	if (pch->ppp)
		goto outl;

	ppp_lock(ppp);
	if (pch->file.hdrlen > ppp->file.hdrlen)
		ppp->file.hdrlen = pch->file.hdrlen;
	hdrlen = pch->file.hdrlen + 2;	/* for protocol bytes */
	if (hdrlen > ppp->dev->hard_header_len)
		ppp->dev->hard_header_len = hdrlen;
	list_add_tail(&pch->clist, &ppp->channels);
	++ppp->n_channels;
	pch->ppp = ppp;
	atomic_inc(&ppp->file.refcnt);
	ppp_unlock(ppp);
	ret = 0;

 outl:
	write_unlock_bh(&pch->upl);
 out:
	mutex_unlock(&pn->all_ppp_mutex);
	return ret;
}