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
typedef  int u16 ;
struct sh_fpu_soft_struct {int dummy; } ;
struct pt_regs {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 unsigned long FPSCR ; 
 unsigned long FPUL ; 
 int /*<<< orphan*/  READ (unsigned long,int) ; 
 int Rn ; 
 int /*<<< orphan*/  WRITE (unsigned long,int) ; 

__attribute__((used)) static int
id_sys(struct sh_fpu_soft_struct *fregs, struct pt_regs *regs, u16 code)
{
	int n = ((code >> 8) & 0xf);
	unsigned long *reg = (code & 0x0010) ? &FPUL : &FPSCR;

	switch (code & 0xf0ff) {
	case 0x005a:
	case 0x006a:
		Rn = *reg;
		break;
	case 0x405a:
	case 0x406a:
		*reg = Rn;
		break;
	case 0x4052:
	case 0x4062:
		Rn -= 4;
		WRITE(*reg, Rn);
		break;
	case 0x4056:
	case 0x4066:
		READ(*reg, Rn);
		Rn += 4;
		break;
	default:
		return -EINVAL;
	}

	return 0;
}