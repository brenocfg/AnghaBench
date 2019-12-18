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
struct ipc_voucher_attr_control {int dummy; } ;
struct ipc_voucher {int dummy; } ;
typedef  int natural_t ;
typedef  size_t iv_index_t ;

/* Variables and functions */
 size_t IV_HASH_BUCKETS ; 
 int MACH_VOUCHER_ATTR_KEY_NUM_WELL_KNOWN ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  Z_NOENCRYPT ; 
 int /*<<< orphan*/  ipc_voucher_attr_control_zone ; 
 int /*<<< orphan*/  ipc_voucher_zone ; 
 int /*<<< orphan*/  ivgt_lock_init () ; 
 int /*<<< orphan*/ * ivht_bucket ; 
 int /*<<< orphan*/  ivht_lock_init () ; 
 int /*<<< orphan*/  queue_init (int /*<<< orphan*/ *) ; 
 int task_max ; 
 int thread_max ; 
 int /*<<< orphan*/  user_data_attr_manager_init () ; 
 int /*<<< orphan*/  zinit (int,int,int,char*) ; 
 int /*<<< orphan*/  zone_change (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void
ipc_voucher_init(void)
{
	natural_t ipc_voucher_max = (task_max + thread_max) * 2;
	natural_t attr_manager_max = MACH_VOUCHER_ATTR_KEY_NUM_WELL_KNOWN;
	iv_index_t i;

	ipc_voucher_zone = zinit(sizeof(struct ipc_voucher),
				 ipc_voucher_max * sizeof(struct ipc_voucher),
				 sizeof(struct ipc_voucher),
				 "ipc vouchers");
	zone_change(ipc_voucher_zone, Z_NOENCRYPT, TRUE);

	ipc_voucher_attr_control_zone = zinit(sizeof(struct ipc_voucher_attr_control),
				 attr_manager_max * sizeof(struct ipc_voucher_attr_control),
				 sizeof(struct ipc_voucher_attr_control),
				 "ipc voucher attr controls");
	zone_change(ipc_voucher_attr_control_zone, Z_NOENCRYPT, TRUE);

	/* initialize voucher hash */
	ivht_lock_init();
	for (i = 0; i < IV_HASH_BUCKETS; i++)
		queue_init(&ivht_bucket[i]);

	/* initialize global table locking */
	ivgt_lock_init();

#if defined(MACH_VOUCHER_ATTR_KEY_USER_DATA) || defined(MACH_VOUCHER_ATTR_KEY_TEST)
	user_data_attr_manager_init();
#endif
}