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
struct gds_vector {int length; } ;
struct gds_subvector {int length; } ;
struct evbuf_header {int length; } ;

/* Variables and functions */
 int /*<<< orphan*/  EBCASC (scalar_t__*,size_t) ; 
 int /*<<< orphan*/  OCF_LENGTH_CPC_NAME ; 
 int /*<<< orphan*/  OCF_LENGTH_HMC_NETWORK ; 
 scalar_t__* cpc_name ; 
 scalar_t__* hmc_network ; 
 int /*<<< orphan*/  memcpy (scalar_t__*,struct gds_vector*,size_t) ; 
 size_t min (int /*<<< orphan*/ ,size_t) ; 
 int /*<<< orphan*/  schedule_work (int /*<<< orphan*/ *) ; 
 struct gds_vector* sclp_find_gds_subvector (struct gds_vector*,void*,int) ; 
 struct gds_vector* sclp_find_gds_vector (struct gds_vector*,void*,int) ; 
 int /*<<< orphan*/  sclp_ocf_change_work ; 
 int /*<<< orphan*/  sclp_ocf_lock ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void sclp_ocf_handler(struct evbuf_header *evbuf)
{
	struct gds_vector *v;
	struct gds_subvector *sv, *netid, *cpc;
	size_t size;

	/* Find the 0x9f00 block. */
	v = sclp_find_gds_vector(evbuf + 1, (void *) evbuf + evbuf->length,
				 0x9f00);
	if (!v)
		return;
	/* Find the 0x9f22 block inside the 0x9f00 block. */
	v = sclp_find_gds_vector(v + 1, (void *) v + v->length, 0x9f22);
	if (!v)
		return;
	/* Find the 0x81 block inside the 0x9f22 block. */
	sv = sclp_find_gds_subvector(v + 1, (void *) v + v->length, 0x81);
	if (!sv)
		return;
	/* Find the 0x01 block inside the 0x81 block. */
	netid = sclp_find_gds_subvector(sv + 1, (void *) sv + sv->length, 1);
	/* Find the 0x02 block inside the 0x81 block. */
	cpc = sclp_find_gds_subvector(sv + 1, (void *) sv + sv->length, 2);
	/* Copy network name and cpc name. */
	spin_lock(&sclp_ocf_lock);
	if (netid) {
		size = min(OCF_LENGTH_HMC_NETWORK, (size_t) netid->length);
		memcpy(hmc_network, netid + 1, size);
		EBCASC(hmc_network, size);
		hmc_network[size] = 0;
	}
	if (cpc) {
		size = min(OCF_LENGTH_CPC_NAME, (size_t) cpc->length);
		memcpy(cpc_name, cpc + 1, size);
		EBCASC(cpc_name, size);
		cpc_name[size] = 0;
	}
	spin_unlock(&sclp_ocf_lock);
	schedule_work(&sclp_ocf_change_work);
}