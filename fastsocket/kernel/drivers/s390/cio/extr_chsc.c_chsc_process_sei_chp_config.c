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
struct chsc_sei_area {scalar_t__ rs; int /*<<< orphan*/  ccdf; } ;
struct chp_id {int id; int /*<<< orphan*/  cssid; } ;
struct chp_config_data {size_t op; int /*<<< orphan*/  map; } ;

/* Variables and functions */
 int /*<<< orphan*/  CIO_CRW_EVENT (int,char*) ; 
 int __MAX_CHPID ; 
 int /*<<< orphan*/  chp_cfg_cancel_deconfigure (struct chp_id) ; 
 int /*<<< orphan*/  chp_cfg_schedule (struct chp_id,int) ; 
 int /*<<< orphan*/  chp_id_init (struct chp_id*) ; 
 int /*<<< orphan*/  chp_test_bit (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  pr_notice (char*,char*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void chsc_process_sei_chp_config(struct chsc_sei_area *sei_area)
{
	struct chp_config_data *data;
	struct chp_id chpid;
	int num;
	char *events[3] = {"configure", "deconfigure", "cancel deconfigure"};

	CIO_CRW_EVENT(4, "chsc: channel-path-configuration notification\n");
	if (sei_area->rs != 0)
		return;
	data = (struct chp_config_data *) &(sei_area->ccdf);
	chp_id_init(&chpid);
	for (num = 0; num <= __MAX_CHPID; num++) {
		if (!chp_test_bit(data->map, num))
			continue;
		chpid.id = num;
		pr_notice("Processing %s for channel path %x.%02x\n",
			  events[data->op], chpid.cssid, chpid.id);
		switch (data->op) {
		case 0:
			chp_cfg_schedule(chpid, 1);
			break;
		case 1:
			chp_cfg_schedule(chpid, 0);
			break;
		case 2:
			chp_cfg_cancel_deconfigure(chpid);
			break;
		}
	}
}