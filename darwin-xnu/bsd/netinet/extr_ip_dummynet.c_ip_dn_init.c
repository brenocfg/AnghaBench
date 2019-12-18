#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_5__ ;
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_11__ {int cmd_len; TYPE_1__* cmd; int /*<<< orphan*/  set; int /*<<< orphan*/  rulenum; scalar_t__ act_ofs; } ;
struct TYPE_10__ {scalar_t__ offset; scalar_t__ elements; scalar_t__ size; } ;
struct TYPE_9__ {scalar_t__ offset; scalar_t__ elements; scalar_t__ size; } ;
struct TYPE_8__ {scalar_t__ offset; scalar_t__ elements; scalar_t__ size; } ;
struct TYPE_7__ {int len; int /*<<< orphan*/  opcode; } ;

/* Variables and functions */
 int /*<<< orphan*/  IPFW_DEFAULT_RULE ; 
 int /*<<< orphan*/  O_ACCEPT ; 
 int /*<<< orphan*/  O_DENY ; 
 int /*<<< orphan*/  RESVD_SET ; 
 int /*<<< orphan*/  bzero (TYPE_5__*,int) ; 
 TYPE_5__ default_rule ; 
 int /*<<< orphan*/  dn_mutex ; 
 int /*<<< orphan*/  dn_mutex_attr ; 
 int /*<<< orphan*/  dn_mutex_grp ; 
 int /*<<< orphan*/  dn_mutex_grp_attr ; 
 int /*<<< orphan*/  dummynet_io ; 
 TYPE_4__ extract_heap ; 
 int /*<<< orphan*/  ip_dn_ctl ; 
 int /*<<< orphan*/  ip_dn_ctl_ptr ; 
 int /*<<< orphan*/  ip_dn_io_ptr ; 
 int /*<<< orphan*/  lck_attr_alloc_init () ; 
 int /*<<< orphan*/  lck_grp_alloc_init (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lck_grp_attr_alloc_init () ; 
 int /*<<< orphan*/  lck_mtx_init (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_3__ ready_heap ; 
 TYPE_2__ wfq_ready_heap ; 

void
ip_dn_init(void)
{
	/* setup locks */
	dn_mutex_grp_attr = lck_grp_attr_alloc_init();
	dn_mutex_grp = lck_grp_alloc_init("dn", dn_mutex_grp_attr);
	dn_mutex_attr = lck_attr_alloc_init();
	lck_mtx_init(dn_mutex, dn_mutex_grp, dn_mutex_attr);

	ready_heap.size = ready_heap.elements = 0 ;
	ready_heap.offset = 0 ;

	wfq_ready_heap.size = wfq_ready_heap.elements = 0 ;
	wfq_ready_heap.offset = 0 ;

	extract_heap.size = extract_heap.elements = 0 ;
	extract_heap.offset = 0 ;
	ip_dn_ctl_ptr = ip_dn_ctl;
	ip_dn_io_ptr = dummynet_io;

	bzero(&default_rule, sizeof default_rule);
#if IPFIREWALL
	default_rule.act_ofs = 0;
	default_rule.rulenum = IPFW_DEFAULT_RULE;
	default_rule.cmd_len = 1;
	default_rule.set = RESVD_SET;

	default_rule.cmd[0].len = 1;
	default_rule.cmd[0].opcode =
#ifdef IPFIREWALL_DEFAULT_TO_ACCEPT
	    (1) ? O_ACCEPT :
#endif
	    O_DENY;
#endif
}