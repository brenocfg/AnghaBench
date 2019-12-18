#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int /*<<< orphan*/  uint64_t ;
typedef  int /*<<< orphan*/  buf ;
struct TYPE_4__ {int dbg_pointer_size; int /*<<< orphan*/  (* write ) (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ;} ;
typedef  int /*<<< orphan*/  Dwarf_Unsigned ;
typedef  int Dwarf_Small ;
typedef  int /*<<< orphan*/  Dwarf_Error ;
typedef  TYPE_1__* Dwarf_Debug ;

/* Variables and functions */
 int /*<<< orphan*/  DWARF_SET_ERROR (TYPE_1__*,int /*<<< orphan*/ *,int) ; 
 int DW_DLE_LOC_EXPR_BAD ; 
 int DW_DLE_NONE ; 
#define  DW_OP_GNU_push_tls_address 273 
#define  DW_OP_abs 272 
#define  DW_OP_addr 271 
#define  DW_OP_and 270 
#define  DW_OP_bra 269 
#define  DW_OP_breg0 268 
#define  DW_OP_breg1 267 
#define  DW_OP_breg10 266 
#define  DW_OP_breg11 265 
#define  DW_OP_breg12 264 
#define  DW_OP_breg13 263 
#define  DW_OP_breg14 262 
#define  DW_OP_breg15 261 
#define  DW_OP_breg16 260 
#define  DW_OP_breg17 259 
#define  DW_OP_breg18 258 
#define  DW_OP_breg19 257 
#define  DW_OP_breg2 256 
#define  DW_OP_breg20 255 
#define  DW_OP_breg21 254 
#define  DW_OP_breg22 253 
#define  DW_OP_breg23 252 
#define  DW_OP_breg24 251 
#define  DW_OP_breg25 250 
#define  DW_OP_breg26 249 
#define  DW_OP_breg27 248 
#define  DW_OP_breg28 247 
#define  DW_OP_breg29 246 
#define  DW_OP_breg3 245 
#define  DW_OP_breg30 244 
#define  DW_OP_breg31 243 
#define  DW_OP_breg4 242 
#define  DW_OP_breg5 241 
#define  DW_OP_breg6 240 
#define  DW_OP_breg7 239 
#define  DW_OP_breg8 238 
#define  DW_OP_breg9 237 
#define  DW_OP_bregx 236 
#define  DW_OP_const1s 235 
#define  DW_OP_const1u 234 
#define  DW_OP_const2s 233 
#define  DW_OP_const2u 232 
#define  DW_OP_const4s 231 
#define  DW_OP_const4u 230 
#define  DW_OP_const8s 229 
#define  DW_OP_const8u 228 
#define  DW_OP_consts 227 
#define  DW_OP_constu 226 
#define  DW_OP_deref 225 
#define  DW_OP_deref_size 224 
#define  DW_OP_div 223 
#define  DW_OP_drop 222 
#define  DW_OP_dup 221 
#define  DW_OP_eq 220 
#define  DW_OP_fbreg 219 
#define  DW_OP_ge 218 
#define  DW_OP_gt 217 
#define  DW_OP_le 216 
#define  DW_OP_lit0 215 
#define  DW_OP_lit1 214 
#define  DW_OP_lit10 213 
#define  DW_OP_lit11 212 
#define  DW_OP_lit12 211 
#define  DW_OP_lit13 210 
#define  DW_OP_lit14 209 
#define  DW_OP_lit15 208 
#define  DW_OP_lit16 207 
#define  DW_OP_lit17 206 
#define  DW_OP_lit18 205 
#define  DW_OP_lit19 204 
#define  DW_OP_lit2 203 
#define  DW_OP_lit20 202 
#define  DW_OP_lit21 201 
#define  DW_OP_lit22 200 
#define  DW_OP_lit23 199 
#define  DW_OP_lit24 198 
#define  DW_OP_lit25 197 
#define  DW_OP_lit26 196 
#define  DW_OP_lit27 195 
#define  DW_OP_lit28 194 
#define  DW_OP_lit29 193 
#define  DW_OP_lit3 192 
#define  DW_OP_lit30 191 
#define  DW_OP_lit31 190 
#define  DW_OP_lit4 189 
#define  DW_OP_lit5 188 
#define  DW_OP_lit6 187 
#define  DW_OP_lit7 186 
#define  DW_OP_lit8 185 
#define  DW_OP_lit9 184 
#define  DW_OP_lt 183 
#define  DW_OP_minus 182 
#define  DW_OP_mod 181 
#define  DW_OP_mul 180 
#define  DW_OP_ne 179 
#define  DW_OP_neg 178 
#define  DW_OP_nop 177 
#define  DW_OP_not 176 
#define  DW_OP_or 175 
#define  DW_OP_over 174 
#define  DW_OP_pick 173 
#define  DW_OP_piece 172 
#define  DW_OP_plus 171 
#define  DW_OP_plus_uconst 170 
#define  DW_OP_reg0 169 
#define  DW_OP_reg1 168 
#define  DW_OP_reg10 167 
#define  DW_OP_reg11 166 
#define  DW_OP_reg12 165 
#define  DW_OP_reg13 164 
#define  DW_OP_reg14 163 
#define  DW_OP_reg15 162 
#define  DW_OP_reg16 161 
#define  DW_OP_reg17 160 
#define  DW_OP_reg18 159 
#define  DW_OP_reg19 158 
#define  DW_OP_reg2 157 
#define  DW_OP_reg20 156 
#define  DW_OP_reg21 155 
#define  DW_OP_reg22 154 
#define  DW_OP_reg23 153 
#define  DW_OP_reg24 152 
#define  DW_OP_reg25 151 
#define  DW_OP_reg26 150 
#define  DW_OP_reg27 149 
#define  DW_OP_reg28 148 
#define  DW_OP_reg29 147 
#define  DW_OP_reg3 146 
#define  DW_OP_reg30 145 
#define  DW_OP_reg31 144 
#define  DW_OP_reg4 143 
#define  DW_OP_reg5 142 
#define  DW_OP_reg6 141 
#define  DW_OP_reg7 140 
#define  DW_OP_reg8 139 
#define  DW_OP_reg9 138 
#define  DW_OP_regx 137 
#define  DW_OP_rot 136 
#define  DW_OP_shl 135 
#define  DW_OP_shr 134 
#define  DW_OP_shra 133 
#define  DW_OP_skip 132 
#define  DW_OP_swap 131 
#define  DW_OP_xderef 130 
#define  DW_OP_xderef_size 129 
#define  DW_OP_xor 128 
 int _dwarf_write_sleb128 (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int _dwarf_write_uleb128 (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  stub2 (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  stub3 (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  stub4 (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 

int
_dwarf_loc_expr_add_atom(Dwarf_Debug dbg, uint8_t *out, uint8_t *end,
    Dwarf_Small atom, Dwarf_Unsigned operand1, Dwarf_Unsigned operand2,
    int *length, Dwarf_Error *error)
{
	uint8_t buf[64];
	uint8_t *p, *pe;
	uint64_t offset;
	int len;

	if (out != NULL && end != NULL) {
		p = out;
		pe = end;
	} else {
		p = out = buf;
		pe = &buf[sizeof(buf)];
	}

	switch (atom) {
	/* Operations with no operands. */
	case DW_OP_deref:
	case DW_OP_reg0:
	case DW_OP_reg1:
	case DW_OP_reg2:
	case DW_OP_reg3:
	case DW_OP_reg4:
	case DW_OP_reg5:
	case DW_OP_reg6:
	case DW_OP_reg7:
	case DW_OP_reg8:
	case DW_OP_reg9:
	case DW_OP_reg10:
	case DW_OP_reg11:
	case DW_OP_reg12:
	case DW_OP_reg13:
	case DW_OP_reg14:
	case DW_OP_reg15:
	case DW_OP_reg16:
	case DW_OP_reg17:
	case DW_OP_reg18:
	case DW_OP_reg19:
	case DW_OP_reg20:
	case DW_OP_reg21:
	case DW_OP_reg22:
	case DW_OP_reg23:
	case DW_OP_reg24:
	case DW_OP_reg25:
	case DW_OP_reg26:
	case DW_OP_reg27:
	case DW_OP_reg28:
	case DW_OP_reg29:
	case DW_OP_reg30:
	case DW_OP_reg31:

	case DW_OP_lit0:
	case DW_OP_lit1:
	case DW_OP_lit2:
	case DW_OP_lit3:
	case DW_OP_lit4:
	case DW_OP_lit5:
	case DW_OP_lit6:
	case DW_OP_lit7:
	case DW_OP_lit8:
	case DW_OP_lit9:
	case DW_OP_lit10:
	case DW_OP_lit11:
	case DW_OP_lit12:
	case DW_OP_lit13:
	case DW_OP_lit14:
	case DW_OP_lit15:
	case DW_OP_lit16:
	case DW_OP_lit17:
	case DW_OP_lit18:
	case DW_OP_lit19:
	case DW_OP_lit20:
	case DW_OP_lit21:
	case DW_OP_lit22:
	case DW_OP_lit23:
	case DW_OP_lit24:
	case DW_OP_lit25:
	case DW_OP_lit26:
	case DW_OP_lit27:
	case DW_OP_lit28:
	case DW_OP_lit29:
	case DW_OP_lit30:
	case DW_OP_lit31:

	case DW_OP_dup:
	case DW_OP_drop:

	case DW_OP_over:

	case DW_OP_swap:
	case DW_OP_rot:
	case DW_OP_xderef:

	case DW_OP_abs:
	case DW_OP_and:
	case DW_OP_div:
	case DW_OP_minus:
	case DW_OP_mod:
	case DW_OP_mul:
	case DW_OP_neg:
	case DW_OP_not:
	case DW_OP_or:
	case DW_OP_plus:

	case DW_OP_shl:
	case DW_OP_shr:
	case DW_OP_shra:
	case DW_OP_xor:

	case DW_OP_eq:
	case DW_OP_ge:
	case DW_OP_gt:
	case DW_OP_le:
	case DW_OP_lt:
	case DW_OP_ne:

	case DW_OP_nop:
	case DW_OP_GNU_push_tls_address:
		*p++ = atom;
		break;

	/* Operations with 1-byte operands. */
	case DW_OP_const1u:
	case DW_OP_const1s:
	case DW_OP_pick:
	case DW_OP_deref_size:
	case DW_OP_xderef_size:
		*p++ = atom;
		*p++ = (uint8_t) operand1;
		break;

	/* Operations with 2-byte operands. */
	case DW_OP_const2u:
	case DW_OP_const2s:
	case DW_OP_bra:
	case DW_OP_skip:
		*p++ = atom;
		offset = 0;
		dbg->write(p, &offset, operand1, 2);
		p += 2;
		break;

	/* Operations with 4-byte operands. */
	case DW_OP_const4u:
	case DW_OP_const4s:
		*p++ = atom;
		offset = 0;
		dbg->write(p, &offset, operand1, 4);
		p += 4;
		break;

	/* Operations with 8-byte operands. */
	case DW_OP_const8u:
	case DW_OP_const8s:
		*p++ = atom;
		offset = 0;
		dbg->write(p, &offset, operand1, 8);
		p += 8;
		break;

	/* Operations with an unsigned LEB128 operand. */
	case DW_OP_constu:
	case DW_OP_plus_uconst:
	case DW_OP_regx:
	case DW_OP_piece:
		*p++ = atom;
		len = _dwarf_write_uleb128(p, pe, operand1);
		assert(len > 0);
		p += len;
		break;

	/* Operations with a signed LEB128 operand. */
	case DW_OP_consts:
	case DW_OP_breg0:
	case DW_OP_breg1:
	case DW_OP_breg2:
	case DW_OP_breg3:
	case DW_OP_breg4:
	case DW_OP_breg5:
	case DW_OP_breg6:
	case DW_OP_breg7:
	case DW_OP_breg8:
	case DW_OP_breg9:
	case DW_OP_breg10:
	case DW_OP_breg11:
	case DW_OP_breg12:
	case DW_OP_breg13:
	case DW_OP_breg14:
	case DW_OP_breg15:
	case DW_OP_breg16:
	case DW_OP_breg17:
	case DW_OP_breg18:
	case DW_OP_breg19:
	case DW_OP_breg20:
	case DW_OP_breg21:
	case DW_OP_breg22:
	case DW_OP_breg23:
	case DW_OP_breg24:
	case DW_OP_breg25:
	case DW_OP_breg26:
	case DW_OP_breg27:
	case DW_OP_breg28:
	case DW_OP_breg29:
	case DW_OP_breg30:
	case DW_OP_breg31:
	case DW_OP_fbreg:
		*p++ = atom;
		len = _dwarf_write_sleb128(p, pe, operand1);
		assert(len > 0);
		p += len;
		break;

	/*
	 * Operations with an unsigned LEB128 operand
	 * followed by a signed LEB128 operand.
	 */
	case DW_OP_bregx:
		*p++ = atom;
		len = _dwarf_write_uleb128(p, pe, operand1);
		assert(len > 0);
		p += len;
		len = _dwarf_write_sleb128(p, pe, operand2);
		assert(len > 0);
		p += len;
		break;

	/* Target address size operand. */
	case DW_OP_addr:
		*p++ = atom;
		offset = 0;
		dbg->write(p, &offset, operand1, dbg->dbg_pointer_size);
		p += dbg->dbg_pointer_size;
		break;

	/* All other operations cause an error. */
	default:
		DWARF_SET_ERROR(dbg, error, DW_DLE_LOC_EXPR_BAD);
		return (DW_DLE_LOC_EXPR_BAD);
	}

	if (length)
		*length = p - out;

	return (DW_DLE_NONE);
}