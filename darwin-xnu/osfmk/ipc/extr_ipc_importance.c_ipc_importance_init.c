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
typedef  int /*<<< orphan*/  temp_buf ;
struct ipc_importance_task {int dummy; } ;
struct ipc_importance_inherit {int dummy; } ;
typedef  int natural_t ;
typedef  int /*<<< orphan*/  mach_voucher_attr_value_handle_t ;
typedef  scalar_t__ kern_return_t ;

/* Variables and functions */
 scalar_t__ KERN_SUCCESS ; 
 int /*<<< orphan*/  MACH_VOUCHER_ATTR_KEY_IMPORTANCE ; 
 scalar_t__ PE_parse_boot_argn (char*,char*,int) ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  Z_NOENCRYPT ; 
 int /*<<< orphan*/  global_iit_alloc_queue ; 
 int /*<<< orphan*/  ipc_importance_control ; 
 int /*<<< orphan*/  ipc_importance_inherit_zone ; 
 int /*<<< orphan*/  ipc_importance_interactive_receiver ; 
 int /*<<< orphan*/  ipc_importance_lock_init () ; 
 int /*<<< orphan*/  ipc_importance_manager ; 
 int /*<<< orphan*/  ipc_importance_task_zone ; 
 scalar_t__ ipc_register_well_known_mach_voucher_attr_manager (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  printf (char*,scalar_t__) ; 
 int /*<<< orphan*/  queue_init (int /*<<< orphan*/ *) ; 
 int task_max ; 
 int thread_max ; 
 int /*<<< orphan*/  zinit (int,int,int,char*) ; 
 int /*<<< orphan*/  zone_change (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void
ipc_importance_init(void)
{
	natural_t ipc_importance_max = (task_max + thread_max) * 2;
	char temp_buf[26];
	kern_return_t kr;

	if (PE_parse_boot_argn("imp_interactive_receiver", temp_buf, sizeof(temp_buf))) {
		ipc_importance_interactive_receiver = TRUE;
	}

	ipc_importance_task_zone = zinit(sizeof(struct ipc_importance_task),
					 ipc_importance_max * sizeof(struct ipc_importance_task),
					 sizeof(struct ipc_importance_task),
					 "ipc task importance");
	zone_change(ipc_importance_task_zone, Z_NOENCRYPT, TRUE);

	ipc_importance_inherit_zone = zinit(sizeof(struct ipc_importance_inherit),
					    ipc_importance_max * sizeof(struct ipc_importance_inherit),
					    sizeof(struct ipc_importance_inherit),
					    "ipc importance inherit");
	zone_change(ipc_importance_inherit_zone, Z_NOENCRYPT, TRUE);


#if DEVELOPMENT || DEBUG 
	queue_init(&global_iit_alloc_queue);
#endif

	/* initialize global locking */
	ipc_importance_lock_init();

	kr = ipc_register_well_known_mach_voucher_attr_manager(&ipc_importance_manager,
						(mach_voucher_attr_value_handle_t)0,
						MACH_VOUCHER_ATTR_KEY_IMPORTANCE,
						&ipc_importance_control);
	if (KERN_SUCCESS != kr)
		printf("Voucher importance manager register returned %d", kr);
}