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
struct kvm_pt_regs {int dummy; } ;
struct ia64_fpreg {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  CASE_FIXED_FP (int) ; 
 unsigned long IA64_FIRST_ROTATING_FR ; 
 unsigned long fph_index (struct kvm_pt_regs*,unsigned long) ; 

void setfpreg(unsigned long regnum, struct ia64_fpreg *fpval,
					struct kvm_pt_regs *regs)
{
	/* Take floating register rotation into consideration*/
	if (regnum >= IA64_FIRST_ROTATING_FR)
		regnum = IA64_FIRST_ROTATING_FR + fph_index(regs, regnum);

#define CASE_FIXED_FP(reg)			\
	case (reg) :				\
		ia64_ldf_fill(reg, fpval);	\
	break

	switch (regnum) {
		CASE_FIXED_FP(2);
		CASE_FIXED_FP(3);
		CASE_FIXED_FP(4);
		CASE_FIXED_FP(5);

		CASE_FIXED_FP(6);
		CASE_FIXED_FP(7);
		CASE_FIXED_FP(8);
		CASE_FIXED_FP(9);
		CASE_FIXED_FP(10);
		CASE_FIXED_FP(11);

		CASE_FIXED_FP(12);
		CASE_FIXED_FP(13);
		CASE_FIXED_FP(14);
		CASE_FIXED_FP(15);
		CASE_FIXED_FP(16);
		CASE_FIXED_FP(17);
		CASE_FIXED_FP(18);
		CASE_FIXED_FP(19);
		CASE_FIXED_FP(20);
		CASE_FIXED_FP(21);
		CASE_FIXED_FP(22);
		CASE_FIXED_FP(23);
		CASE_FIXED_FP(24);
		CASE_FIXED_FP(25);
		CASE_FIXED_FP(26);
		CASE_FIXED_FP(27);
		CASE_FIXED_FP(28);
		CASE_FIXED_FP(29);
		CASE_FIXED_FP(30);
		CASE_FIXED_FP(31);
		CASE_FIXED_FP(32);
		CASE_FIXED_FP(33);
		CASE_FIXED_FP(34);
		CASE_FIXED_FP(35);
		CASE_FIXED_FP(36);
		CASE_FIXED_FP(37);
		CASE_FIXED_FP(38);
		CASE_FIXED_FP(39);
		CASE_FIXED_FP(40);
		CASE_FIXED_FP(41);
		CASE_FIXED_FP(42);
		CASE_FIXED_FP(43);
		CASE_FIXED_FP(44);
		CASE_FIXED_FP(45);
		CASE_FIXED_FP(46);
		CASE_FIXED_FP(47);
		CASE_FIXED_FP(48);
		CASE_FIXED_FP(49);
		CASE_FIXED_FP(50);
		CASE_FIXED_FP(51);
		CASE_FIXED_FP(52);
		CASE_FIXED_FP(53);
		CASE_FIXED_FP(54);
		CASE_FIXED_FP(55);
		CASE_FIXED_FP(56);
		CASE_FIXED_FP(57);
		CASE_FIXED_FP(58);
		CASE_FIXED_FP(59);
		CASE_FIXED_FP(60);
		CASE_FIXED_FP(61);
		CASE_FIXED_FP(62);
		CASE_FIXED_FP(63);
		CASE_FIXED_FP(64);
		CASE_FIXED_FP(65);
		CASE_FIXED_FP(66);
		CASE_FIXED_FP(67);
		CASE_FIXED_FP(68);
		CASE_FIXED_FP(69);
		CASE_FIXED_FP(70);
		CASE_FIXED_FP(71);
		CASE_FIXED_FP(72);
		CASE_FIXED_FP(73);
		CASE_FIXED_FP(74);
		CASE_FIXED_FP(75);
		CASE_FIXED_FP(76);
		CASE_FIXED_FP(77);
		CASE_FIXED_FP(78);
		CASE_FIXED_FP(79);
		CASE_FIXED_FP(80);
		CASE_FIXED_FP(81);
		CASE_FIXED_FP(82);
		CASE_FIXED_FP(83);
		CASE_FIXED_FP(84);
		CASE_FIXED_FP(85);
		CASE_FIXED_FP(86);
		CASE_FIXED_FP(87);
		CASE_FIXED_FP(88);
		CASE_FIXED_FP(89);
		CASE_FIXED_FP(90);
		CASE_FIXED_FP(91);
		CASE_FIXED_FP(92);
		CASE_FIXED_FP(93);
		CASE_FIXED_FP(94);
		CASE_FIXED_FP(95);
		CASE_FIXED_FP(96);
		CASE_FIXED_FP(97);
		CASE_FIXED_FP(98);
		CASE_FIXED_FP(99);
		CASE_FIXED_FP(100);
		CASE_FIXED_FP(101);
		CASE_FIXED_FP(102);
		CASE_FIXED_FP(103);
		CASE_FIXED_FP(104);
		CASE_FIXED_FP(105);
		CASE_FIXED_FP(106);
		CASE_FIXED_FP(107);
		CASE_FIXED_FP(108);
		CASE_FIXED_FP(109);
		CASE_FIXED_FP(110);
		CASE_FIXED_FP(111);
		CASE_FIXED_FP(112);
		CASE_FIXED_FP(113);
		CASE_FIXED_FP(114);
		CASE_FIXED_FP(115);
		CASE_FIXED_FP(116);
		CASE_FIXED_FP(117);
		CASE_FIXED_FP(118);
		CASE_FIXED_FP(119);
		CASE_FIXED_FP(120);
		CASE_FIXED_FP(121);
		CASE_FIXED_FP(122);
		CASE_FIXED_FP(123);
		CASE_FIXED_FP(124);
		CASE_FIXED_FP(125);
		CASE_FIXED_FP(126);
		CASE_FIXED_FP(127);
	}
}