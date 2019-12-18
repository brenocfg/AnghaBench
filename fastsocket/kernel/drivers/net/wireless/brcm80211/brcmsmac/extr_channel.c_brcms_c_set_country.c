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
struct brcms_regd {int dummy; } ;
struct brcms_cm_info {struct brcms_c_info* wlc; } ;
struct brcms_c_info {TYPE_2__* protection; int /*<<< orphan*/ * bandstate; TYPE_1__* pub; } ;
struct TYPE_4__ {int nmode_user; int /*<<< orphan*/  gmode_user; } ;
struct TYPE_3__ {int _n_enab; } ;

/* Variables and functions */
 size_t BAND_2G_INDEX ; 
 size_t BAND_5G_INDEX ; 
 int SUPPORT_11N ; 
 int /*<<< orphan*/  brcms_c_set_gmode (struct brcms_c_info*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  brcms_c_set_nmode (struct brcms_c_info*) ; 
 int /*<<< orphan*/  brcms_c_stf_ss_update (struct brcms_c_info*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
brcms_c_set_country(struct brcms_cm_info *wlc_cm,
		    const struct brcms_regd *regd)
{
	struct brcms_c_info *wlc = wlc_cm->wlc;

	if ((wlc->pub->_n_enab & SUPPORT_11N) !=
	    wlc->protection->nmode_user)
		brcms_c_set_nmode(wlc);

	brcms_c_stf_ss_update(wlc, wlc->bandstate[BAND_2G_INDEX]);
	brcms_c_stf_ss_update(wlc, wlc->bandstate[BAND_5G_INDEX]);

	brcms_c_set_gmode(wlc, wlc->protection->gmode_user, false);

	return;
}