#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct bfad_s {int dummy; } ;
struct bfa_ioc_s {int /*<<< orphan*/  ioc_aen_seq; TYPE_2__* attr; TYPE_1__* bfa; } ;
struct TYPE_7__ {int ioc_type; void* mac; int /*<<< orphan*/  pwwn; } ;
struct TYPE_8__ {TYPE_3__ ioc; } ;
struct bfa_aen_entry_s {TYPE_4__ aen_data; } ;
typedef  enum bfa_ioc_type_e { ____Placeholder_bfa_ioc_type_e } bfa_ioc_type_e ;
typedef  enum bfa_ioc_aen_event { ____Placeholder_bfa_ioc_aen_event } bfa_ioc_aen_event ;
struct TYPE_6__ {int /*<<< orphan*/  pwwn; } ;
struct TYPE_5__ {scalar_t__ bfad; } ;

/* Variables and functions */
 int /*<<< orphan*/  BFA_AEN_CAT_IOC ; 
#define  BFA_IOC_TYPE_FC 130 
#define  BFA_IOC_TYPE_FCoE 129 
#define  BFA_IOC_TYPE_LL 128 
 int /*<<< orphan*/  WARN_ON (int) ; 
 void* bfa_ioc_get_mac (struct bfa_ioc_s*) ; 
 int bfa_ioc_get_type (struct bfa_ioc_s*) ; 
 int /*<<< orphan*/  bfad_get_aen_entry (struct bfad_s*,struct bfa_aen_entry_s*) ; 
 int /*<<< orphan*/  bfad_im_post_vendor_event (struct bfa_aen_entry_s*,struct bfad_s*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

void
bfa_ioc_aen_post(struct bfa_ioc_s *ioc, enum bfa_ioc_aen_event event)
{
	struct bfad_s *bfad = (struct bfad_s *)ioc->bfa->bfad;
	struct bfa_aen_entry_s	*aen_entry;
	enum bfa_ioc_type_e ioc_type;

	bfad_get_aen_entry(bfad, aen_entry);
	if (!aen_entry)
		return;

	ioc_type = bfa_ioc_get_type(ioc);
	switch (ioc_type) {
	case BFA_IOC_TYPE_FC:
		aen_entry->aen_data.ioc.pwwn = ioc->attr->pwwn;
		break;
	case BFA_IOC_TYPE_FCoE:
		aen_entry->aen_data.ioc.pwwn = ioc->attr->pwwn;
		aen_entry->aen_data.ioc.mac = bfa_ioc_get_mac(ioc);
		break;
	case BFA_IOC_TYPE_LL:
		aen_entry->aen_data.ioc.mac = bfa_ioc_get_mac(ioc);
		break;
	default:
		WARN_ON(ioc_type != BFA_IOC_TYPE_FC);
		break;
	}

	/* Send the AEN notification */
	aen_entry->aen_data.ioc.ioc_type = ioc_type;
	bfad_im_post_vendor_event(aen_entry, bfad, ++ioc->ioc_aen_seq,
				  BFA_AEN_CAT_IOC, event);
}