#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  tBTM_CB ;
struct TYPE_3__ {int /*<<< orphan*/  trace_level; void* sec_pending_q; void* page_queue; } ;

/* Variables and functions */
 int /*<<< orphan*/  BTM_INITIAL_TRACE_LEVEL ; 
 int /*<<< orphan*/  BTM_SEC_MODE_SP ; 
 int /*<<< orphan*/  BT_TRACE_LEVEL_NONE ; 
 int /*<<< orphan*/  QUEUE_SIZE_MAX ; 
 int /*<<< orphan*/  btm_acl_init () ; 
 int /*<<< orphan*/  btm_ble_lock_init () ; 
 int /*<<< orphan*/  btm_ble_sem_init () ; 
 TYPE_1__ btm_cb ; 
 int /*<<< orphan*/ * btm_cb_ptr ; 
 int /*<<< orphan*/  btm_dev_init () ; 
 int /*<<< orphan*/  btm_inq_db_init () ; 
 int /*<<< orphan*/  btm_sco_init () ; 
 int /*<<< orphan*/  btm_sec_init (int /*<<< orphan*/ ) ; 
 void* fixed_queue_new (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (TYPE_1__*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ osi_malloc (int) ; 

void btm_init (void)
{
#if BTM_DYNAMIC_MEMORY
    btm_cb_ptr = (tBTM_CB *)osi_malloc(sizeof(tBTM_CB));
#endif /* #if BTM_DYNAMIC_MEMORY */
    /* All fields are cleared; nonzero fields are reinitialized in appropriate function */
    memset(&btm_cb, 0, sizeof(tBTM_CB));
    btm_cb.page_queue = fixed_queue_new(QUEUE_SIZE_MAX);
    btm_cb.sec_pending_q = fixed_queue_new(QUEUE_SIZE_MAX);

#if defined(BTM_INITIAL_TRACE_LEVEL)
    btm_cb.trace_level = BTM_INITIAL_TRACE_LEVEL;
#else
    btm_cb.trace_level = BT_TRACE_LEVEL_NONE;
#endif
    /* Initialize BTM component structures */
    btm_inq_db_init();                  /* Inquiry Database and Structures */
    btm_acl_init();                     /* ACL Database and Structures */
#if (SMP_INCLUDED == TRUE)
    btm_sec_init(BTM_SEC_MODE_SP);      /* Security Manager Database and Structures */
#endif  ///SMP_INCLUDED == TRUE
#if BTM_SCO_INCLUDED == TRUE
    btm_sco_init();                     /* SCO Database and Structures (If included) */
#endif

    btm_dev_init();                     /* Device Manager Structures & HCI_Reset */
#if BLE_INCLUDED == TRUE
    btm_ble_lock_init();
    btm_ble_sem_init();
#endif
}