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
struct TYPE_4__ {int fpc; } ;
struct TYPE_5__ {TYPE_1__ fp_regs; } ;
struct TYPE_6__ {TYPE_2__ thread; } ;

/* Variables and functions */
 int SIGFPE ; 
 int SIGILL ; 
 TYPE_3__* current ; 
#define  emu_adbr 185 
#define  emu_aebr 184 
#define  emu_axbr 183 
#define  emu_cdbr 182 
#define  emu_cdfbr 181 
#define  emu_cebr 180 
#define  emu_cefbr 179 
#define  emu_cfdbr 178 
#define  emu_cfebr 177 
#define  emu_cfxbr 176 
#define  emu_cxbr 175 
#define  emu_cxfbr 174 
#define  emu_ddbr 173 
#define  emu_debr 172 
#define  emu_didbr 171 
#define  emu_diebr 170 
#define  emu_dxbr 169 
#define  emu_efpc 168 
#define  emu_fidbr 167 
#define  emu_fiebr 166 
#define  emu_fixbr 165 
#define  emu_kdbr 164 
#define  emu_kebr 163 
#define  emu_kxbr 162 
#define  emu_lcdbr 161 
#define  emu_lcebr 160 
#define  emu_lcxbr 159 
#define  emu_ldebr 158 
#define  emu_ldxbr 157 
#define  emu_ledbr 156 
#define  emu_lexbr 155 
#define  emu_lndbr 154 
#define  emu_lnebr 153 
#define  emu_lnxbr 152 
 int /*<<< orphan*/  emu_load_regd (int) ; 
 int /*<<< orphan*/  emu_load_rege (int) ; 
#define  emu_lpdbr 151 
#define  emu_lpebr 150 
#define  emu_lpxbr 149 
#define  emu_ltdbr 148 
#define  emu_ltebr 147 
#define  emu_ltxbr 146 
#define  emu_lxdbr 145 
#define  emu_lxebr 144 
#define  emu_madbr 143 
#define  emu_maebr 142 
#define  emu_mdbr 141 
#define  emu_mdebr 140 
#define  emu_meebr 139 
#define  emu_msdbr 138 
#define  emu_msebr 137 
#define  emu_mxbr 136 
#define  emu_mxdbr 135 
#define  emu_sdbr 134 
#define  emu_sebr 133 
#define  emu_sfpc 132 
#define  emu_sqdbr 131 
#define  emu_sqebr 130 
#define  emu_sqxbr 129 
 int /*<<< orphan*/  emu_store_regd (int) ; 
 int /*<<< orphan*/  emu_store_rege (int) ; 
#define  emu_sxbr 128 
 int stub1 (struct pt_regs*,int,int) ; 
 int stub10 (struct pt_regs*,int,int,int) ; 
 int stub11 (struct pt_regs*,int,int,int) ; 
 int stub12 (struct pt_regs*,int,int,int) ; 
 int stub13 (struct pt_regs*,int,int) ; 
 int stub14 (struct pt_regs*,int,int) ; 
 int stub15 (struct pt_regs*,int,int) ; 
 int stub16 (struct pt_regs*,int,int) ; 
 int stub17 (struct pt_regs*,int,int) ; 
 int stub18 (struct pt_regs*,int,int) ; 
 int stub19 (struct pt_regs*,int,int) ; 
 int stub2 (struct pt_regs*,int,int) ; 
 int stub3 (struct pt_regs*,int,int) ; 
 int stub4 (struct pt_regs*,int,int,int) ; 
 int stub5 (struct pt_regs*,int,int,int) ; 
 int stub6 (struct pt_regs*,int,int,int) ; 
 int stub7 (struct pt_regs*,int,int) ; 
 int stub8 (struct pt_regs*,int,int) ; 
 int stub9 (struct pt_regs*,int,int) ; 

int math_emu_b3(__u8 *opcode, struct pt_regs * regs) {
        int _fex = 0;
        static const __u8 format_table[256] = {
                [0x00] = 0x03,[0x01] = 0x03,[0x02] = 0x03,[0x03] = 0x03,
		[0x04] = 0x0f,[0x05] = 0x0d,[0x06] = 0x0e,[0x07] = 0x0d,
		[0x08] = 0x03,[0x09] = 0x03,[0x0a] = 0x03,[0x0b] = 0x03,
                [0x0c] = 0x0f,[0x0d] = 0x03,[0x0e] = 0x06,[0x0f] = 0x06,
		[0x10] = 0x02,[0x11] = 0x02,[0x12] = 0x02,[0x13] = 0x02,
		[0x14] = 0x03,[0x15] = 0x02,[0x16] = 0x01,[0x17] = 0x03,
                [0x18] = 0x02,[0x19] = 0x02,[0x1a] = 0x02,[0x1b] = 0x02,
		[0x1c] = 0x02,[0x1d] = 0x02,[0x1e] = 0x05,[0x1f] = 0x05,
		[0x40] = 0x01,[0x41] = 0x01,[0x42] = 0x01,[0x43] = 0x01,
                [0x44] = 0x12,[0x45] = 0x0d,[0x46] = 0x11,[0x47] = 0x04,
		[0x48] = 0x01,[0x49] = 0x01,[0x4a] = 0x01,[0x4b] = 0x01,
		[0x4c] = 0x01,[0x4d] = 0x01,[0x53] = 0x06,[0x57] = 0x06,
                [0x5b] = 0x05,[0x5f] = 0x05,[0x84] = 0x13,[0x8c] = 0x13,
		[0x94] = 0x09,[0x95] = 0x08,[0x96] = 0x07,[0x98] = 0x0c,
		[0x99] = 0x0b,[0x9a] = 0x0a
        };
        static const void *jump_table[256]= {
                [0x00] = emu_lpebr,[0x01] = emu_lnebr,[0x02] = emu_ltebr,
                [0x03] = emu_lcebr,[0x04] = emu_ldebr,[0x05] = emu_lxdbr,
                [0x06] = emu_lxebr,[0x07] = emu_mxdbr,[0x08] = emu_kebr,
                [0x09] = emu_cebr, [0x0a] = emu_aebr, [0x0b] = emu_sebr,
                [0x0c] = emu_mdebr,[0x0d] = emu_debr, [0x0e] = emu_maebr,
                [0x0f] = emu_msebr,[0x10] = emu_lpdbr,[0x11] = emu_lndbr, 
                [0x12] = emu_ltdbr,[0x13] = emu_lcdbr,[0x14] = emu_sqebr,
                [0x15] = emu_sqdbr,[0x16] = emu_sqxbr,[0x17] = emu_meebr,
                [0x18] = emu_kdbr, [0x19] = emu_cdbr, [0x1a] = emu_adbr,
                [0x1b] = emu_sdbr, [0x1c] = emu_mdbr, [0x1d] = emu_ddbr,  
                [0x1e] = emu_madbr,[0x1f] = emu_msdbr,[0x40] = emu_lpxbr,
                [0x41] = emu_lnxbr,[0x42] = emu_ltxbr,[0x43] = emu_lcxbr,
                [0x44] = emu_ledbr,[0x45] = emu_ldxbr,[0x46] = emu_lexbr,
                [0x47] = emu_fixbr,[0x48] = emu_kxbr, [0x49] = emu_cxbr,  
                [0x4a] = emu_axbr, [0x4b] = emu_sxbr, [0x4c] = emu_mxbr,
                [0x4d] = emu_dxbr, [0x53] = emu_diebr,[0x57] = emu_fiebr,
                [0x5b] = emu_didbr,[0x5f] = emu_fidbr,[0x84] = emu_sfpc,
                [0x8c] = emu_efpc, [0x94] = emu_cefbr,[0x95] = emu_cdfbr, 
                [0x96] = emu_cxfbr,[0x98] = emu_cfebr,[0x99] = emu_cfdbr,
                [0x9a] = emu_cfxbr
        };

        switch (format_table[opcode[1]]) {
        case 1: /* RRE format, long double operation */
                if (opcode[3] & 0x22)
			return SIGILL;
                emu_store_regd((opcode[3] >> 4) & 15);
                emu_store_regd(((opcode[3] >> 4) & 15) + 2);
                emu_store_regd(opcode[3] & 15);
                emu_store_regd((opcode[3] & 15) + 2);
                /* call the emulation function */
                _fex = ((int (*)(struct pt_regs *,int, int))
			jump_table[opcode[1]])
                        (regs, opcode[3] >> 4, opcode[3] & 15);
                emu_load_regd((opcode[3] >> 4) & 15);
                emu_load_regd(((opcode[3] >> 4) & 15) + 2);
                emu_load_regd(opcode[3] & 15);
                emu_load_regd((opcode[3] & 15) + 2);
		break;
        case 2: /* RRE format, double operation */
                emu_store_regd((opcode[3] >> 4) & 15);
                emu_store_regd(opcode[3] & 15);
                /* call the emulation function */
                _fex = ((int (*)(struct pt_regs *, int, int))
			jump_table[opcode[1]])
                        (regs, opcode[3] >> 4, opcode[3] & 15);
                emu_load_regd((opcode[3] >> 4) & 15);
                emu_load_regd(opcode[3] & 15);
		break;
        case 3: /* RRE format, float operation */
                emu_store_rege((opcode[3] >> 4) & 15);
                emu_store_rege(opcode[3] & 15);
                /* call the emulation function */
                _fex = ((int (*)(struct pt_regs *, int, int))
			jump_table[opcode[1]])
                        (regs, opcode[3] >> 4, opcode[3] & 15);
                emu_load_rege((opcode[3] >> 4) & 15);
                emu_load_rege(opcode[3] & 15);
		break;
        case 4: /* RRF format, long double operation */
                if (opcode[3] & 0x22)
			return SIGILL;
                emu_store_regd((opcode[3] >> 4) & 15);
                emu_store_regd(((opcode[3] >> 4) & 15) + 2);
                emu_store_regd(opcode[3] & 15);
                emu_store_regd((opcode[3] & 15) + 2);
                /* call the emulation function */
                _fex = ((int (*)(struct pt_regs *, int, int, int))
			jump_table[opcode[1]])
                        (regs, opcode[3] >> 4, opcode[3] & 15, opcode[2] >> 4);
                emu_load_regd((opcode[3] >> 4) & 15);
                emu_load_regd(((opcode[3] >> 4) & 15) + 2);
                emu_load_regd(opcode[3] & 15);
                emu_load_regd((opcode[3] & 15) + 2);
		break;
        case 5: /* RRF format, double operation */
                emu_store_regd((opcode[2] >> 4) & 15);
                emu_store_regd((opcode[3] >> 4) & 15);
                emu_store_regd(opcode[3] & 15);
                /* call the emulation function */
                _fex = ((int (*)(struct pt_regs *, int, int, int))
			jump_table[opcode[1]])
                        (regs, opcode[3] >> 4, opcode[3] & 15, opcode[2] >> 4);
                emu_load_regd((opcode[2] >> 4) & 15);
                emu_load_regd((opcode[3] >> 4) & 15);
                emu_load_regd(opcode[3] & 15);
		break;
        case 6: /* RRF format, float operation */
                emu_store_rege((opcode[2] >> 4) & 15);
                emu_store_rege((opcode[3] >> 4) & 15);
                emu_store_rege(opcode[3] & 15);
                /* call the emulation function */
                _fex = ((int (*)(struct pt_regs *, int, int, int))
			jump_table[opcode[1]])
                        (regs, opcode[3] >> 4, opcode[3] & 15, opcode[2] >> 4);
                emu_load_rege((opcode[2] >> 4) & 15);
                emu_load_rege((opcode[3] >> 4) & 15);
                emu_load_rege(opcode[3] & 15);
		break;
        case 7: /* RRE format, cxfbr instruction */
                /* call the emulation function */
                if (opcode[3] & 0x20)
			return SIGILL;
                _fex = ((int (*)(struct pt_regs *, int, int))
			jump_table[opcode[1]])
                        (regs, opcode[3] >> 4, opcode[3] & 15);
                emu_load_regd((opcode[3] >> 4) & 15);
                emu_load_regd(((opcode[3] >> 4) & 15) + 2);
		break;
        case 8: /* RRE format, cdfbr instruction */
                /* call the emulation function */
                _fex = ((int (*)(struct pt_regs *, int, int))
			jump_table[opcode[1]])
                        (regs, opcode[3] >> 4, opcode[3] & 15);
                emu_load_regd((opcode[3] >> 4) & 15);
		break;
        case 9: /* RRE format, cefbr instruction */
                /* call the emulation function */
                _fex = ((int (*)(struct pt_regs *, int, int))
			jump_table[opcode[1]])
                        (regs, opcode[3] >> 4, opcode[3] & 15);
                emu_load_rege((opcode[3] >> 4) & 15);
		break;
        case 10: /* RRF format, cfxbr instruction */
                if ((opcode[2] & 128) == 128 || (opcode[2] & 96) == 32)
			/* mask of { 2,3,8-15 } is invalid */
			return SIGILL;
                if (opcode[3] & 2)
			return SIGILL;
                emu_store_regd(opcode[3] & 15);
                emu_store_regd((opcode[3] & 15) + 2);
                /* call the emulation function */
                _fex = ((int (*)(struct pt_regs *, int, int, int))
			jump_table[opcode[1]])
                        (regs, opcode[3] >> 4, opcode[3] & 15, opcode[2] >> 4);
		break;
        case 11: /* RRF format, cfdbr instruction */
                if ((opcode[2] & 128) == 128 || (opcode[2] & 96) == 32)
			/* mask of { 2,3,8-15 } is invalid */
			return SIGILL;
                emu_store_regd(opcode[3] & 15);
                /* call the emulation function */
                _fex = ((int (*)(struct pt_regs *, int, int, int))
			jump_table[opcode[1]])
                        (regs, opcode[3] >> 4, opcode[3] & 15, opcode[2] >> 4);
		break;
        case 12: /* RRF format, cfebr instruction */
                if ((opcode[2] & 128) == 128 || (opcode[2] & 96) == 32)
			/* mask of { 2,3,8-15 } is invalid */
			return SIGILL;
                emu_store_rege(opcode[3] & 15);
                /* call the emulation function */
                _fex = ((int (*)(struct pt_regs *, int, int, int))
			jump_table[opcode[1]])
                        (regs, opcode[3] >> 4, opcode[3] & 15, opcode[2] >> 4);
		break;
        case 13: /* RRE format, ldxbr & mdxbr instruction */
                /* double store but long double load */
                if (opcode[3] & 0x20)
			return SIGILL;
                emu_store_regd((opcode[3] >> 4) & 15);
                emu_store_regd(opcode[3]  & 15);
                /* call the emulation function */
                _fex = ((int (*)(struct pt_regs *, int, int))
			jump_table[opcode[1]])
                        (regs, opcode[3] >> 4, opcode[3] & 15);
                emu_load_regd((opcode[3] >> 4) & 15);
                emu_load_regd(((opcode[3] >> 4) & 15) + 2);
		break;
        case 14: /* RRE format, ldxbr & mdxbr instruction */
                /* float store but long double load */
                if (opcode[3] & 0x20)
			return SIGILL;
                emu_store_rege((opcode[3] >> 4) & 15);
                emu_store_rege(opcode[3]  & 15);
                /* call the emulation function */
                _fex = ((int (*)(struct pt_regs *, int, int))
			jump_table[opcode[1]])
                        (regs, opcode[3] >> 4, opcode[3] & 15);
                emu_load_regd((opcode[3] >> 4) & 15);
                emu_load_regd(((opcode[3] >> 4) & 15) + 2);
		break;
        case 15: /* RRE format, ldebr & mdebr instruction */
                /* float store but double load */
                emu_store_rege((opcode[3] >> 4) & 15);
                emu_store_rege(opcode[3]  & 15);
                /* call the emulation function */
                _fex = ((int (*)(struct pt_regs *, int, int))
			jump_table[opcode[1]])
                        (regs, opcode[3] >> 4, opcode[3] & 15);
                emu_load_regd((opcode[3] >> 4) & 15);
		break;
        case 16: /* RRE format, ldxbr instruction */
                /* long double store but double load */
                if (opcode[3] & 2)
			return SIGILL;
                emu_store_regd(opcode[3] & 15);
                emu_store_regd((opcode[3] & 15) + 2);
                /* call the emulation function */
                _fex = ((int (*)(struct pt_regs *, int, int))
			jump_table[opcode[1]])
                        (regs, opcode[3] >> 4, opcode[3] & 15);
                emu_load_regd((opcode[3] >> 4) & 15);
                break;
        case 17: /* RRE format, ldxbr instruction */
                /* long double store but float load */
                if (opcode[3] & 2)
			return SIGILL;
                emu_store_regd(opcode[3] & 15);
                emu_store_regd((opcode[3] & 15) + 2);
                /* call the emulation function */
                _fex = ((int (*)(struct pt_regs *, int, int))
			jump_table[opcode[1]])
                        (regs, opcode[3] >> 4, opcode[3] & 15);
                emu_load_rege((opcode[3] >> 4) & 15);
                break;
        case 18: /* RRE format, ledbr instruction */
                /* double store but float load */
                emu_store_regd(opcode[3] & 15);
                /* call the emulation function */
                _fex = ((int (*)(struct pt_regs *, int, int))
			jump_table[opcode[1]])
                        (regs, opcode[3] >> 4, opcode[3] & 15);
                emu_load_rege((opcode[3] >> 4) & 15);
                break;
        case 19: /* RRE format, efpc & sfpc instruction */
                /* call the emulation function */
                _fex = ((int (*)(struct pt_regs *, int, int))
			jump_table[opcode[1]])
                        (regs, opcode[3] >> 4, opcode[3] & 15);
                break;
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