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
typedef  size_t uint_t ;
struct TYPE_3__ {size_t dtdo_len; int /*<<< orphan*/ * dtdo_buf; } ;
typedef  TYPE_1__ dtrace_difo_t ;
typedef  int /*<<< orphan*/  dif_instr_t ;

/* Variables and functions */
 size_t DIF_INSTR_OP (int /*<<< orphan*/ ) ; 
 size_t DIF_INSTR_SUBR (int /*<<< orphan*/ ) ; 
 size_t DIF_INSTR_VAR (int /*<<< orphan*/ ) ; 
#define  DIF_OP_ADD 197 
#define  DIF_OP_ALLOCS 196 
#define  DIF_OP_AND 195 
#define  DIF_OP_BA 194 
#define  DIF_OP_BE 193 
#define  DIF_OP_BG 192 
#define  DIF_OP_BGE 191 
#define  DIF_OP_BGEU 190 
#define  DIF_OP_BGU 189 
#define  DIF_OP_BL 188 
#define  DIF_OP_BLE 187 
#define  DIF_OP_BLEU 186 
#define  DIF_OP_BLU 185 
#define  DIF_OP_BNE 184 
#define  DIF_OP_CALL 183 
#define  DIF_OP_CMP 182 
#define  DIF_OP_COPYS 181 
#define  DIF_OP_FLUSHTS 180 
#define  DIF_OP_LDGA 179 
#define  DIF_OP_LDGAA 178 
#define  DIF_OP_LDGS 177 
#define  DIF_OP_LDLS 176 
#define  DIF_OP_LDTA 175 
#define  DIF_OP_LDTAA 174 
#define  DIF_OP_LDTS 173 
#define  DIF_OP_MOV 172 
#define  DIF_OP_MUL 171 
#define  DIF_OP_NOP 170 
#define  DIF_OP_NOT 169 
#define  DIF_OP_OR 168 
#define  DIF_OP_POPTS 167 
#define  DIF_OP_PUSHTR 166 
#define  DIF_OP_PUSHTV 165 
#define  DIF_OP_RET 164 
#define  DIF_OP_RLDSB 163 
#define  DIF_OP_RLDSH 162 
#define  DIF_OP_RLDSW 161 
#define  DIF_OP_RLDUB 160 
#define  DIF_OP_RLDUH 159 
#define  DIF_OP_RLDUW 158 
#define  DIF_OP_RLDX 157 
#define  DIF_OP_SCMP 156 
#define  DIF_OP_SDIV 155 
#define  DIF_OP_SETS 154 
#define  DIF_OP_SETX 153 
#define  DIF_OP_SLL 152 
#define  DIF_OP_SRA 151 
#define  DIF_OP_SREM 150 
#define  DIF_OP_SRL 149 
#define  DIF_OP_STB 148 
#define  DIF_OP_STGAA 147 
#define  DIF_OP_STGS 146 
#define  DIF_OP_STH 145 
#define  DIF_OP_STLS 144 
#define  DIF_OP_STTAA 143 
#define  DIF_OP_STTS 142 
#define  DIF_OP_STW 141 
#define  DIF_OP_STX 140 
#define  DIF_OP_SUB 139 
#define  DIF_OP_TST 138 
#define  DIF_OP_UDIV 137 
#define  DIF_OP_ULDSB 136 
#define  DIF_OP_ULDSH 135 
#define  DIF_OP_ULDSW 134 
#define  DIF_OP_ULDUB 133 
#define  DIF_OP_ULDUH 132 
#define  DIF_OP_ULDUW 131 
#define  DIF_OP_ULDX 130 
#define  DIF_OP_UREM 129 
#define  DIF_OP_XOR 128 
 size_t DIF_SUBR_ALLOCA ; 
 size_t DIF_SUBR_BCOPY ; 
 size_t DIF_SUBR_COPYIN ; 
 size_t DIF_SUBR_COPYINSTR ; 
 size_t DIF_SUBR_COPYINTO ; 
 size_t DIF_SUBR_HTONL ; 
 size_t DIF_SUBR_HTONLL ; 
 size_t DIF_SUBR_HTONS ; 
 size_t DIF_SUBR_INDEX ; 
 size_t DIF_SUBR_INET_NTOA ; 
 size_t DIF_SUBR_INET_NTOA6 ; 
 size_t DIF_SUBR_INET_NTOP ; 
 size_t DIF_SUBR_KDEBUG_TRACE ; 
 size_t DIF_SUBR_KDEBUG_TRACE_STRING ; 
 size_t DIF_SUBR_LLTOSTR ; 
 size_t DIF_SUBR_NTOHL ; 
 size_t DIF_SUBR_NTOHLL ; 
 size_t DIF_SUBR_NTOHS ; 
 size_t DIF_SUBR_RINDEX ; 
 size_t DIF_SUBR_STRCHR ; 
 size_t DIF_SUBR_STRJOIN ; 
 size_t DIF_SUBR_STRRCHR ; 
 size_t DIF_SUBR_STRSTR ; 
 size_t DIF_VAR_ARG0 ; 
 size_t DIF_VAR_ARG9 ; 
 size_t DIF_VAR_CURTHREAD ; 
 size_t DIF_VAR_EXECNAME ; 
 size_t DIF_VAR_GID ; 
 size_t DIF_VAR_OTHER_UBASE ; 
 size_t DIF_VAR_PID ; 
 size_t DIF_VAR_PPID ; 
 size_t DIF_VAR_TID ; 
 size_t DIF_VAR_UID ; 
 size_t DIF_VAR_ZONENAME ; 
 int dtrace_difo_err (uint_t,char const*) ; 

__attribute__((used)) static int
dtrace_difo_validate_helper(dtrace_difo_t *dp)
{
	int (*efunc)(uint_t pc, const char *, ...) = dtrace_difo_err;
	int err = 0;
	uint_t pc;

	for (pc = 0; pc < dp->dtdo_len; pc++) {
		dif_instr_t instr = dp->dtdo_buf[pc];

		uint_t v = DIF_INSTR_VAR(instr);
		uint_t subr = DIF_INSTR_SUBR(instr);
		uint_t op = DIF_INSTR_OP(instr);

		switch (op) {
		case DIF_OP_OR:
		case DIF_OP_XOR:
		case DIF_OP_AND:
		case DIF_OP_SLL:
		case DIF_OP_SRL:
		case DIF_OP_SRA:
		case DIF_OP_SUB:
		case DIF_OP_ADD:
		case DIF_OP_MUL:
		case DIF_OP_SDIV:
		case DIF_OP_UDIV:
		case DIF_OP_SREM:
		case DIF_OP_UREM:
		case DIF_OP_COPYS:
		case DIF_OP_NOT:
		case DIF_OP_MOV:
		case DIF_OP_RLDSB:
		case DIF_OP_RLDSH:
		case DIF_OP_RLDSW:
		case DIF_OP_RLDUB:
		case DIF_OP_RLDUH:
		case DIF_OP_RLDUW:
		case DIF_OP_RLDX:
		case DIF_OP_ULDSB:
		case DIF_OP_ULDSH:
		case DIF_OP_ULDSW:
		case DIF_OP_ULDUB:
		case DIF_OP_ULDUH:
		case DIF_OP_ULDUW:
		case DIF_OP_ULDX:
		case DIF_OP_STB:
		case DIF_OP_STH:
		case DIF_OP_STW:
		case DIF_OP_STX:
		case DIF_OP_ALLOCS:
		case DIF_OP_CMP:
		case DIF_OP_SCMP:
		case DIF_OP_TST:
		case DIF_OP_BA:
		case DIF_OP_BE:
		case DIF_OP_BNE:
		case DIF_OP_BG:
		case DIF_OP_BGU:
		case DIF_OP_BGE:
		case DIF_OP_BGEU:
		case DIF_OP_BL:
		case DIF_OP_BLU:
		case DIF_OP_BLE:
		case DIF_OP_BLEU:
		case DIF_OP_RET:
		case DIF_OP_NOP:
		case DIF_OP_POPTS:
		case DIF_OP_FLUSHTS:
		case DIF_OP_SETX:
		case DIF_OP_SETS:
		case DIF_OP_LDGA:
		case DIF_OP_LDLS:
		case DIF_OP_STGS:
		case DIF_OP_STLS:
		case DIF_OP_PUSHTR:
		case DIF_OP_PUSHTV:
			break;

		case DIF_OP_LDGS:
			if (v >= DIF_VAR_OTHER_UBASE)
				break;

			if (v >= DIF_VAR_ARG0 && v <= DIF_VAR_ARG9)
				break;

			if (v == DIF_VAR_CURTHREAD || v == DIF_VAR_PID ||
			    v == DIF_VAR_PPID || v == DIF_VAR_TID ||
			    v == DIF_VAR_EXECNAME || v == DIF_VAR_ZONENAME ||
			    v == DIF_VAR_UID || v == DIF_VAR_GID)
				break;

			err += efunc(pc, "illegal variable %u\n", v);
			break;

		case DIF_OP_LDTA:
		case DIF_OP_LDTS:
		case DIF_OP_LDGAA:
		case DIF_OP_LDTAA:
			err += efunc(pc, "illegal dynamic variable load\n");
			break;

		case DIF_OP_STTS:
		case DIF_OP_STGAA:
		case DIF_OP_STTAA:
			err += efunc(pc, "illegal dynamic variable store\n");
			break;

		case DIF_OP_CALL:
			if (subr == DIF_SUBR_ALLOCA ||
			    subr == DIF_SUBR_BCOPY ||
			    subr == DIF_SUBR_COPYIN ||
			    subr == DIF_SUBR_COPYINTO ||
			    subr == DIF_SUBR_COPYINSTR ||
			    subr == DIF_SUBR_INDEX ||
			    subr == DIF_SUBR_INET_NTOA ||
			    subr == DIF_SUBR_INET_NTOA6 ||
			    subr == DIF_SUBR_INET_NTOP ||
			    subr == DIF_SUBR_LLTOSTR ||
			    subr == DIF_SUBR_RINDEX ||
			    subr == DIF_SUBR_STRCHR ||
			    subr == DIF_SUBR_STRJOIN ||
			    subr == DIF_SUBR_STRRCHR ||
			    subr == DIF_SUBR_STRSTR ||
			    subr == DIF_SUBR_KDEBUG_TRACE ||
			    subr == DIF_SUBR_KDEBUG_TRACE_STRING ||
			    subr == DIF_SUBR_HTONS ||
			    subr == DIF_SUBR_HTONL ||
			    subr == DIF_SUBR_HTONLL ||
			    subr == DIF_SUBR_NTOHS ||
			    subr == DIF_SUBR_NTOHL ||
			    subr == DIF_SUBR_NTOHLL)
				break;

			err += efunc(pc, "invalid subr %u\n", subr);
			break;

		default:
			err += efunc(pc, "invalid opcode %u\n",
			    DIF_INSTR_OP(instr));
		}
	}

	return (err);
}