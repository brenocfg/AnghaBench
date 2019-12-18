#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_26__   TYPE_9__ ;
typedef  struct TYPE_25__   TYPE_8__ ;
typedef  struct TYPE_24__   TYPE_7__ ;
typedef  struct TYPE_23__   TYPE_6__ ;
typedef  struct TYPE_22__   TYPE_5__ ;
typedef  struct TYPE_21__   TYPE_4__ ;
typedef  struct TYPE_20__   TYPE_3__ ;
typedef  struct TYPE_19__   TYPE_2__ ;
typedef  struct TYPE_18__   TYPE_1__ ;
typedef  struct TYPE_17__   TYPE_13__ ;
typedef  struct TYPE_16__   TYPE_12__ ;
typedef  struct TYPE_15__   TYPE_11__ ;
typedef  struct TYPE_14__   TYPE_10__ ;

/* Type definitions */
struct kvm_vcpu {int /*<<< orphan*/  vcpu_id; } ;
struct TYPE_15__ {int /*<<< orphan*/ * bits; } ;
struct TYPE_16__ {TYPE_11__ u; } ;
struct TYPE_26__ {int /*<<< orphan*/ * bits; } ;
struct TYPE_14__ {TYPE_9__ u; } ;
struct TYPE_24__ {int /*<<< orphan*/ * bits; } ;
struct TYPE_25__ {TYPE_7__ u; } ;
struct TYPE_22__ {int /*<<< orphan*/ * bits; } ;
struct TYPE_23__ {TYPE_5__ u; } ;
struct TYPE_20__ {int /*<<< orphan*/ * bits; } ;
struct TYPE_21__ {TYPE_3__ u; } ;
struct TYPE_18__ {int /*<<< orphan*/ * bits; } ;
struct TYPE_19__ {TYPE_1__ u; } ;
struct kvm_pt_regs {unsigned long cr_iip; unsigned long ar_rsc; unsigned long pr; unsigned long ar_fpsr; unsigned long b7; unsigned long r3; unsigned long r10; unsigned long r13; unsigned long r16; unsigned long r19; unsigned long r22; unsigned long r25; unsigned long r28; unsigned long r31; int /*<<< orphan*/  r30; int /*<<< orphan*/  r29; int /*<<< orphan*/  r27; int /*<<< orphan*/  r26; int /*<<< orphan*/  r24; int /*<<< orphan*/  r23; int /*<<< orphan*/  r21; int /*<<< orphan*/  r20; int /*<<< orphan*/  r18; int /*<<< orphan*/  r17; int /*<<< orphan*/  r15; int /*<<< orphan*/  r14; int /*<<< orphan*/  r12; int /*<<< orphan*/  r11; int /*<<< orphan*/  r9; int /*<<< orphan*/  r8; int /*<<< orphan*/  r2; int /*<<< orphan*/  r1; TYPE_12__ f11; TYPE_10__ f10; TYPE_8__ f9; TYPE_6__ f8; TYPE_4__ f7; TYPE_2__ f6; int /*<<< orphan*/  b6; int /*<<< orphan*/  b0; int /*<<< orphan*/  ar_ssd; int /*<<< orphan*/  ar_csd; int /*<<< orphan*/  ar_ccv; int /*<<< orphan*/  loadrs; int /*<<< orphan*/  ar_bspstore; int /*<<< orphan*/  ar_rnat; int /*<<< orphan*/  ar_pfs; int /*<<< orphan*/  ar_unat; int /*<<< orphan*/  cr_ifs; int /*<<< orphan*/  cr_ipsr; } ;
struct TYPE_17__ {unsigned long ri; } ;

/* Variables and functions */
 struct kvm_vcpu* current_vcpu ; 
 TYPE_13__* ia64_psr (struct kvm_pt_regs*) ; 
 int /*<<< orphan*/  printk (char*,struct kvm_vcpu*,int /*<<< orphan*/ ,...) ; 

__attribute__((used)) static void kvm_show_registers(struct kvm_pt_regs *regs)
{
	unsigned long ip = regs->cr_iip + ia64_psr(regs)->ri;

	struct kvm_vcpu *vcpu = current_vcpu;
	if (vcpu != NULL)
		printk("vcpu 0x%p vcpu %d\n",
		       vcpu, vcpu->vcpu_id);

	printk("psr : %016lx ifs : %016lx ip  : [<%016lx>]\n",
	       regs->cr_ipsr, regs->cr_ifs, ip);

	printk("unat: %016lx pfs : %016lx rsc : %016lx\n",
	       regs->ar_unat, regs->ar_pfs, regs->ar_rsc);
	printk("rnat: %016lx bspstore: %016lx pr  : %016lx\n",
	       regs->ar_rnat, regs->ar_bspstore, regs->pr);
	printk("ldrs: %016lx ccv : %016lx fpsr: %016lx\n",
	       regs->loadrs, regs->ar_ccv, regs->ar_fpsr);
	printk("csd : %016lx ssd : %016lx\n", regs->ar_csd, regs->ar_ssd);
	printk("b0  : %016lx b6  : %016lx b7  : %016lx\n", regs->b0,
							regs->b6, regs->b7);
	printk("f6  : %05lx%016lx f7  : %05lx%016lx\n",
	       regs->f6.u.bits[1], regs->f6.u.bits[0],
	       regs->f7.u.bits[1], regs->f7.u.bits[0]);
	printk("f8  : %05lx%016lx f9  : %05lx%016lx\n",
	       regs->f8.u.bits[1], regs->f8.u.bits[0],
	       regs->f9.u.bits[1], regs->f9.u.bits[0]);
	printk("f10 : %05lx%016lx f11 : %05lx%016lx\n",
	       regs->f10.u.bits[1], regs->f10.u.bits[0],
	       regs->f11.u.bits[1], regs->f11.u.bits[0]);

	printk("r1  : %016lx r2  : %016lx r3  : %016lx\n", regs->r1,
							regs->r2, regs->r3);
	printk("r8  : %016lx r9  : %016lx r10 : %016lx\n", regs->r8,
							regs->r9, regs->r10);
	printk("r11 : %016lx r12 : %016lx r13 : %016lx\n", regs->r11,
							regs->r12, regs->r13);
	printk("r14 : %016lx r15 : %016lx r16 : %016lx\n", regs->r14,
							regs->r15, regs->r16);
	printk("r17 : %016lx r18 : %016lx r19 : %016lx\n", regs->r17,
							regs->r18, regs->r19);
	printk("r20 : %016lx r21 : %016lx r22 : %016lx\n", regs->r20,
							regs->r21, regs->r22);
	printk("r23 : %016lx r24 : %016lx r25 : %016lx\n", regs->r23,
							regs->r24, regs->r25);
	printk("r26 : %016lx r27 : %016lx r28 : %016lx\n", regs->r26,
							regs->r27, regs->r28);
	printk("r29 : %016lx r30 : %016lx r31 : %016lx\n", regs->r29,
							regs->r30, regs->r31);

}