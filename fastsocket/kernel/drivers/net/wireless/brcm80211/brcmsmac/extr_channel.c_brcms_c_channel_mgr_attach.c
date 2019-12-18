#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_5__ ;
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct ssb_sprom {char* alpha2; } ;
struct brcms_pub {int /*<<< orphan*/  srom_ccode; } ;
struct brcms_cm_info {TYPE_5__* world_regd; struct brcms_c_info* wlc; struct brcms_pub* pub; } ;
struct brcms_c_info {int /*<<< orphan*/  autocountry_default; int /*<<< orphan*/  country_default; struct brcms_pub* pub; struct brcms_cm_info* cmi; TYPE_3__* hw; } ;
struct TYPE_12__ {TYPE_4__* regdomain; } ;
struct TYPE_11__ {char* alpha2; } ;
struct TYPE_10__ {TYPE_2__* d11core; } ;
struct TYPE_9__ {TYPE_1__* bus; } ;
struct TYPE_8__ {struct ssb_sprom sprom; } ;

/* Variables and functions */
 int BRCM_CNTRY_BUF_SZ ; 
 int /*<<< orphan*/  GFP_ATOMIC ; 
 scalar_t__ brcms_c_country_valid (char const*) ; 
 int /*<<< orphan*/  brcms_c_set_country (struct brcms_cm_info*,TYPE_5__*) ; 
 TYPE_5__* brcms_default_world_regd () ; 
 TYPE_5__* brcms_world_regd (char const*,int) ; 
 struct brcms_cm_info* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strncpy (int /*<<< orphan*/ ,char const*,int) ; 

struct brcms_cm_info *brcms_c_channel_mgr_attach(struct brcms_c_info *wlc)
{
	struct brcms_cm_info *wlc_cm;
	struct brcms_pub *pub = wlc->pub;
	struct ssb_sprom *sprom = &wlc->hw->d11core->bus->sprom;
	const char *ccode = sprom->alpha2;
	int ccode_len = sizeof(sprom->alpha2);

	wlc_cm = kzalloc(sizeof(struct brcms_cm_info), GFP_ATOMIC);
	if (wlc_cm == NULL)
		return NULL;
	wlc_cm->pub = pub;
	wlc_cm->wlc = wlc;
	wlc->cmi = wlc_cm;

	/* store the country code for passing up as a regulatory hint */
	wlc_cm->world_regd = brcms_world_regd(ccode, ccode_len);
	if (brcms_c_country_valid(ccode))
		strncpy(wlc->pub->srom_ccode, ccode, ccode_len);

	/*
	 * If no custom world domain is found in the SROM, use the
	 * default "X2" domain.
	 */
	if (!wlc_cm->world_regd) {
		wlc_cm->world_regd = brcms_default_world_regd();
		ccode = wlc_cm->world_regd->regdomain->alpha2;
		ccode_len = BRCM_CNTRY_BUF_SZ - 1;
	}

	/* save default country for exiting 11d regulatory mode */
	strncpy(wlc->country_default, ccode, ccode_len);

	/* initialize autocountry_default to driver default */
	strncpy(wlc->autocountry_default, ccode, ccode_len);

	brcms_c_set_country(wlc_cm, wlc_cm->world_regd);

	return wlc_cm;
}