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
typedef  int /*<<< orphan*/  ap_qid_t ;

/* Variables and functions */
 int AP_DEVICES ; 
 int AP_DOMAINS ; 
 int /*<<< orphan*/  AP_MKQID (int,int) ; 
 int ENODEV ; 
 int ap_domain_index ; 
 int ap_query_queue (int /*<<< orphan*/ ,int*,int*) ; 
 int /*<<< orphan*/  ap_test_config_card_id (int) ; 
 int /*<<< orphan*/  ap_test_config_domain (int) ; 

__attribute__((used)) static int ap_select_domain(void)
{
	int queue_depth, device_type, count, max_count, best_domain;
	ap_qid_t qid;
	int rc, i, j;

	/*
	 * We want to use a single domain. Either the one specified with
	 * the "domain=" parameter or the domain with the maximum number
	 * of devices.
	 */
	if (ap_domain_index >= 0 && ap_domain_index < AP_DOMAINS)
		/* Domain has already been selected. */
		return 0;
	best_domain = -1;
	max_count = 0;
	for (i = 0; i < AP_DOMAINS; i++) {
		if (!ap_test_config_domain(i))
			continue;
		count = 0;
		for (j = 0; j < AP_DEVICES; j++) {
			if (!ap_test_config_card_id(j))
				continue;
			qid = AP_MKQID(j, i);
			rc = ap_query_queue(qid, &queue_depth, &device_type);
			if (rc)
				continue;
			count++;
		}
		if (count > max_count) {
			max_count = count;
			best_domain = i;
		}
	}
	if (best_domain >= 0){
		ap_domain_index = best_domain;
		return 0;
	}
	return -ENODEV;
}