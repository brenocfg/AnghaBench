#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct pt_regs {int dummy; } ;
typedef  int __u8 ;
typedef  long __u64 ;
typedef  int __u32 ;
struct TYPE_4__ {int fpc; } ;
struct TYPE_5__ {TYPE_1__ fp_regs; } ;
struct TYPE_6__ {TYPE_2__ thread; } ;

/* Variables and functions */
 int SIGFPE ; 
 int SIGILL ; 
 scalar_t__ calc_addr (struct pt_regs*,int,int,int) ; 
 TYPE_3__* current ; 
#define  emu_adb 153 
#define  emu_aeb 152 
#define  emu_cdb 151 
#define  emu_ceb 150 
#define  emu_ddb 149 
#define  emu_deb 148 
#define  emu_kdb 147 
#define  emu_keb 146 
#define  emu_ldeb 145 
 int /*<<< orphan*/  emu_load_regd (int) ; 
 int /*<<< orphan*/  emu_load_rege (int) ; 
#define  emu_lxdb 144 
#define  emu_lxeb 143 
#define  emu_madb 142 
#define  emu_maeb 141 
#define  emu_mdb 140 
#define  emu_mdeb 139 
#define  emu_meeb 138 
#define  emu_msdb 137 
#define  emu_mseb 136 
#define  emu_mxdb 135 
#define  emu_sdb 134 
#define  emu_seb 133 
#define  emu_sqdb 132 
#define  emu_sqeb 131 
 int /*<<< orphan*/  emu_store_regd (int) ; 
 int /*<<< orphan*/  emu_store_rege (int) ; 
#define  emu_tcdb 130 
#define  emu_tceb 129 
#define  emu_tcxb 128 
 int /*<<< orphan*/  mathemu_copy_from_user (long*,long*,int) ; 
 int /*<<< orphan*/  mathemu_get_user (int,int*) ; 
 int stub1 (struct pt_regs*,int,double*) ; 
 int stub10 (struct pt_regs*,int,long) ; 
 int stub2 (struct pt_regs*,int,float*) ; 
 int stub3 (struct pt_regs*,int,double*,int) ; 
 int stub4 (struct pt_regs*,int,float*,int) ; 
 int stub5 (struct pt_regs*,int,double*) ; 
 int stub6 (struct pt_regs*,int,float*) ; 
 int stub7 (struct pt_regs*,int,float*) ; 
 int stub8 (struct pt_regs*,int,long) ; 
 int stub9 (struct pt_regs*,int,long) ; 

int math_emu_ed(__u8 *opcode, struct pt_regs * regs) {
        int _fex = 0;

        static const __u8 format_table[256] = {
                [0x04] = 0x06,[0x05] = 0x05,[0x06] = 0x07,[0x07] = 0x05,
		[0x08] = 0x02,[0x09] = 0x02,[0x0a] = 0x02,[0x0b] = 0x02,
		[0x0c] = 0x06,[0x0d] = 0x02,[0x0e] = 0x04,[0x0f] = 0x04,
                [0x10] = 0x08,[0x11] = 0x09,[0x12] = 0x0a,[0x14] = 0x02,
		[0x15] = 0x01,[0x17] = 0x02,[0x18] = 0x01,[0x19] = 0x01,
		[0x1a] = 0x01,[0x1b] = 0x01,[0x1c] = 0x01,[0x1d] = 0x01,
                [0x1e] = 0x03,[0x1f] = 0x03,
        };
        static const void *jump_table[]= {
                [0x04] = emu_ldeb,[0x05] = emu_lxdb,[0x06] = emu_lxeb,
                [0x07] = emu_mxdb,[0x08] = emu_keb, [0x09] = emu_ceb,
                [0x0a] = emu_aeb, [0x0b] = emu_seb, [0x0c] = emu_mdeb,
                [0x0d] = emu_deb, [0x0e] = emu_maeb,[0x0f] = emu_mseb,
                [0x10] = emu_tceb,[0x11] = emu_tcdb,[0x12] = emu_tcxb,
                [0x14] = emu_sqeb,[0x15] = emu_sqdb,[0x17] = emu_meeb,
                [0x18] = emu_kdb, [0x19] = emu_cdb, [0x1a] = emu_adb,
                [0x1b] = emu_sdb, [0x1c] = emu_mdb, [0x1d] = emu_ddb,
                [0x1e] = emu_madb,[0x1f] = emu_msdb
        };

        switch (format_table[opcode[5]]) {
        case 1: /* RXE format, double constant */ {
                __u64 *dxb, temp;
                __u32 opc;

                emu_store_regd((opcode[1] >> 4) & 15);
                opc = *((__u32 *) opcode);
                dxb = (__u64 *) calc_addr(regs, opc >> 16, opc >> 12, opc);
                mathemu_copy_from_user(&temp, dxb, 8);
                /* call the emulation function */
                _fex = ((int (*)(struct pt_regs *, int, double *))
			jump_table[opcode[5]])
                        (regs, opcode[1] >> 4, (double *) &temp);
                emu_load_regd((opcode[1] >> 4) & 15);
                break;
        }
        case 2: /* RXE format, float constant */ {
                __u32 *dxb, temp;
                __u32 opc;

                emu_store_rege((opcode[1] >> 4) & 15);
                opc = *((__u32 *) opcode);
                dxb = (__u32 *) calc_addr(regs, opc >> 16, opc >> 12, opc);
                mathemu_get_user(temp, dxb);
                /* call the emulation function */
                _fex = ((int (*)(struct pt_regs *, int, float *))
			jump_table[opcode[5]])
                        (regs, opcode[1] >> 4, (float *) &temp);
                emu_load_rege((opcode[1] >> 4) & 15);
                break;
        }
        case 3: /* RXF format, double constant */ {
                __u64 *dxb, temp;
                __u32 opc;

                emu_store_regd((opcode[1] >> 4) & 15);
                emu_store_regd((opcode[4] >> 4) & 15);
                opc = *((__u32 *) opcode);
                dxb = (__u64 *) calc_addr(regs, opc >> 16, opc >> 12, opc);
                mathemu_copy_from_user(&temp, dxb, 8);
                /* call the emulation function */
                _fex = ((int (*)(struct pt_regs *, int, double *, int))
			jump_table[opcode[5]])
                        (regs, opcode[1] >> 4, (double *) &temp, opcode[4] >> 4);
                emu_load_regd((opcode[1] >> 4) & 15);
                break;
        }
        case 4: /* RXF format, float constant */ {
                __u32 *dxb, temp;
                __u32 opc;

                emu_store_rege((opcode[1] >> 4) & 15);
                emu_store_rege((opcode[4] >> 4) & 15);
                opc = *((__u32 *) opcode);
                dxb = (__u32 *) calc_addr(regs, opc >> 16, opc >> 12, opc);
                mathemu_get_user(temp, dxb);
                /* call the emulation function */
                _fex = ((int (*)(struct pt_regs *, int, float *, int))
			jump_table[opcode[5]])
                        (regs, opcode[1] >> 4, (float *) &temp, opcode[4] >> 4);
                emu_load_rege((opcode[4] >> 4) & 15);
                break;
        }
        case 5: /* RXE format, double constant */
                /* store double and load long double */ 
        {
                __u64 *dxb, temp;
                __u32 opc;
                if ((opcode[1] >> 4) & 0x20)
			return SIGILL;
                emu_store_regd((opcode[1] >> 4) & 15);
                opc = *((__u32 *) opcode);
                dxb = (__u64 *) calc_addr(regs, opc >> 16, opc >> 12, opc);
                mathemu_copy_from_user(&temp, dxb, 8);
                /* call the emulation function */
                _fex = ((int (*)(struct pt_regs *, int, double *))
			jump_table[opcode[5]])
                        (regs, opcode[1] >> 4, (double *) &temp);
                emu_load_regd((opcode[1] >> 4) & 15);
                emu_load_regd(((opcode[1] >> 4) & 15) + 2);
                break;
        }
        case 6: /* RXE format, float constant */
                /* store float and load double */ 
        {
                __u32 *dxb, temp;
                __u32 opc;
                emu_store_rege((opcode[1] >> 4) & 15);
                opc = *((__u32 *) opcode);
                dxb = (__u32 *) calc_addr(regs, opc >> 16, opc >> 12, opc);
                mathemu_get_user(temp, dxb);
                /* call the emulation function */
                _fex = ((int (*)(struct pt_regs *, int, float *))
			jump_table[opcode[5]])
                        (regs, opcode[1] >> 4, (float *) &temp);
                emu_load_regd((opcode[1] >> 4) & 15);
                break;
        }
        case 7: /* RXE format, float constant */
                /* store float and load long double */ 
        {
                __u32 *dxb, temp;
                __u32 opc;
                if ((opcode[1] >> 4) & 0x20)
			return SIGILL;
                emu_store_rege((opcode[1] >> 4) & 15);
                opc = *((__u32 *) opcode);
                dxb = (__u32 *) calc_addr(regs, opc >> 16, opc >> 12, opc);
                mathemu_get_user(temp, dxb);
                /* call the emulation function */
                _fex = ((int (*)(struct pt_regs *, int, float *))
			jump_table[opcode[5]])
                        (regs, opcode[1] >> 4, (float *) &temp);
                emu_load_regd((opcode[1] >> 4) & 15);
                emu_load_regd(((opcode[1] >> 4) & 15) + 2);
                break;
        }
        case 8: /* RXE format, RX address used as int value */ {
                __u64 dxb;
                __u32 opc;

                emu_store_rege((opcode[1] >> 4) & 15);
                opc = *((__u32 *) opcode);
                dxb = (__u64) calc_addr(regs, opc >> 16, opc >> 12, opc);
                /* call the emulation function */
                _fex = ((int (*)(struct pt_regs *, int, long))
			jump_table[opcode[5]])
                        (regs, opcode[1] >> 4, dxb);
                break;
        }
        case 9: /* RXE format, RX address used as int value */ {
                __u64 dxb;
                __u32 opc;

                emu_store_regd((opcode[1] >> 4) & 15);
                opc = *((__u32 *) opcode);
                dxb = (__u64) calc_addr(regs, opc >> 16, opc >> 12, opc);
                /* call the emulation function */
                _fex = ((int (*)(struct pt_regs *, int, long))
			jump_table[opcode[5]])
                        (regs, opcode[1] >> 4, dxb);
                break;
        }
        case 10: /* RXE format, RX address used as int value */ {
                __u64 dxb;
                __u32 opc;

                if ((opcode[1] >> 4) & 2)
			return SIGILL;
                emu_store_regd((opcode[1] >> 4) & 15);
                emu_store_regd(((opcode[1] >> 4) & 15) + 2);
                opc = *((__u32 *) opcode);
                dxb = (__u64) calc_addr(regs, opc >> 16, opc >> 12, opc);
                /* call the emulation function */
                _fex = ((int (*)(struct pt_regs *, int, long))
			jump_table[opcode[5]])
                        (regs, opcode[1] >> 4, dxb);
                break;
        }
        default: /* invalid operation */
                return SIGILL;
        }
	if (_fex != 0) {
		current->thread.fp_regs.fpc |= _fex;
		if (current->thread.fp_regs.fpc & (_fex << 8))
			return SIGFPE;
	}
	return 0;
}