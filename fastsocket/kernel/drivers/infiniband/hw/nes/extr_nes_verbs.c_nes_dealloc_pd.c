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
struct nes_vnic {struct nes_device* nesdev; } ;
struct nes_ucontext {size_t first_free_db; scalar_t__* mmap_db_index; int /*<<< orphan*/  allocated_doorbells; } ;
struct nes_pd {size_t mmap_db_index; int pd_id; } ;
struct nes_device {struct nes_adapter* nesadapter; } ;
struct nes_adapter {int base_pd; int /*<<< orphan*/  allocated_pds; } ;
struct ib_pd {TYPE_1__* uobject; int /*<<< orphan*/  device; } ;
struct TYPE_2__ {scalar_t__ context; } ;

/* Variables and functions */
 int /*<<< orphan*/  NES_DBG_PD ; 
 int PAGE_SHIFT ; 
 int /*<<< orphan*/  clear_bit (size_t,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct nes_pd*) ; 
 int /*<<< orphan*/  nes_debug (int /*<<< orphan*/ ,char*,int,...) ; 
 int /*<<< orphan*/  nes_free_resource (struct nes_adapter*,int /*<<< orphan*/ ,int) ; 
 struct nes_pd* to_nespd (struct ib_pd*) ; 
 struct nes_ucontext* to_nesucontext (scalar_t__) ; 
 struct nes_vnic* to_nesvnic (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int nes_dealloc_pd(struct ib_pd *ibpd)
{
	struct nes_ucontext *nesucontext;
	struct nes_pd *nespd = to_nespd(ibpd);
	struct nes_vnic *nesvnic = to_nesvnic(ibpd->device);
	struct nes_device *nesdev = nesvnic->nesdev;
	struct nes_adapter *nesadapter = nesdev->nesadapter;

	if ((ibpd->uobject) && (ibpd->uobject->context)) {
		nesucontext = to_nesucontext(ibpd->uobject->context);
		nes_debug(NES_DBG_PD, "Clearing bit %u from allocated doorbells\n",
				nespd->mmap_db_index);
		clear_bit(nespd->mmap_db_index, nesucontext->allocated_doorbells);
		nesucontext->mmap_db_index[nespd->mmap_db_index] = 0;
		if (nesucontext->first_free_db > nespd->mmap_db_index) {
			nesucontext->first_free_db = nespd->mmap_db_index;
		}
	}

	nes_debug(NES_DBG_PD, "Deallocating PD%u structure located @%p.\n",
			nespd->pd_id, nespd);
	nes_free_resource(nesadapter, nesadapter->allocated_pds,
			(nespd->pd_id-nesadapter->base_pd)>>(PAGE_SHIFT-12));
	kfree(nespd);

	return 0;
}