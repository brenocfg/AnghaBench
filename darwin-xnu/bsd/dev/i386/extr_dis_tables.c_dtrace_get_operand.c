#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ uint_t ;
struct TYPE_8__ {scalar_t__ d86_numopnds; int d86_rex_prefix; scalar_t__ d86_opnd_size; scalar_t__ d86_addr_size; scalar_t__ d86_mode; scalar_t__ d86_vsib; TYPE_1__* d86_opnd; scalar_t__ d86_error; } ;
typedef  TYPE_2__ dis86_t ;
struct TYPE_7__ {char* d86_opnd; void* d86_mode; } ;

/* Variables and functions */
#define  BYTE_OPND 137 
#define  CONTROL_OPND 136 
#define  DEBUG_OPND 135 
 scalar_t__ EBP_REGNO ; 
 scalar_t__ ESP_REGNO ; 
#define  LONG_OPND 134 
#define  MM_OPND 133 
 void* MODE_NONE ; 
 void* MODE_OFFSET ; 
 void* MODE_RIPREL ; 
 void* MODE_SIGNED ; 
 int /*<<< orphan*/  OPLEN ; 
 scalar_t__ REG_ONLY ; 
 int REX_B ; 
 int REX_X ; 
#define  SEG_OPND 132 
 scalar_t__ SIZE16 ; 
 scalar_t__ SIZE32 ; 
#define  TEST_OPND 131 
#define  WORD_OPND 130 
#define  XMM_OPND 129 
#define  YMM_OPND 128 
 char** dis_CONTROLREG ; 
 char** dis_DEBUGREG ; 
 char** dis_MMREG ; 
 char** dis_REG16 ; 
 char** dis_REG32 ; 
 char** dis_REG64 ; 
 char** dis_REG8 ; 
 char** dis_REG8_REX ; 
 char** dis_SEGREG ; 
 char** dis_TESTREG ; 
 char** dis_XMMREG ; 
 char** dis_YMMREG ; 
 char*** dis_addr16 ; 
 char** dis_addr32_mode0 ; 
 char** dis_addr32_mode12 ; 
 char** dis_addr64_mode0 ; 
 char** dis_addr64_mode12 ; 
 char** dis_scale_factor ; 
 char** dis_vscale_factor ; 
 int /*<<< orphan*/  dtrace_check_override (TYPE_2__*,int) ; 
 int /*<<< orphan*/  dtrace_get_SIB (TYPE_2__*,scalar_t__*,scalar_t__*,scalar_t__*) ; 
 int /*<<< orphan*/  dtrace_imm_opnd (TYPE_2__*,int const,int,int) ; 
 int /*<<< orphan*/  strlcat (char*,char const* const,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
dtrace_get_operand(dis86_t *x, uint_t mode, uint_t r_m, int wbit, int opindex)
{
	int have_SIB = 0;	/* flag presence of scale-index-byte */
	uint_t ss;		/* scale-factor from opcode */
	uint_t index;		/* index register number */
	uint_t base;		/* base register number */
	int dispsize;   	/* size of displacement in bytes */
#ifdef DIS_TEXT
	char *opnd = x->d86_opnd[opindex].d86_opnd;
#else
	#pragma unused (wbit)
#endif

	if (x->d86_numopnds < (uint_t)opindex + 1)
		x->d86_numopnds = (uint_t)opindex + 1;

	if (x->d86_error)
		return;

	/*
	 * first handle a simple register
	 */
	if (mode == REG_ONLY) {
#ifdef DIS_TEXT
		switch (wbit) {
		case MM_OPND:
			(void) strlcat(opnd, dis_MMREG[r_m], OPLEN);
			break;
		case XMM_OPND:
			(void) strlcat(opnd, dis_XMMREG[r_m], OPLEN);
			break;
		case YMM_OPND:
			(void) strlcat(opnd, dis_YMMREG[r_m], OPLEN);
			break;
		case SEG_OPND:
			(void) strlcat(opnd, dis_SEGREG[r_m], OPLEN);
			break;
		case CONTROL_OPND:
			(void) strlcat(opnd, dis_CONTROLREG[r_m], OPLEN);
			break;
		case DEBUG_OPND:
			(void) strlcat(opnd, dis_DEBUGREG[r_m], OPLEN);
			break;
		case TEST_OPND:
			(void) strlcat(opnd, dis_TESTREG[r_m], OPLEN);
			break;
		case BYTE_OPND:
			if (x->d86_rex_prefix == 0)
				(void) strlcat(opnd, dis_REG8[r_m], OPLEN);
			else
				(void) strlcat(opnd, dis_REG8_REX[r_m], OPLEN);
			break;
		case WORD_OPND:
			(void) strlcat(opnd, dis_REG16[r_m], OPLEN);
			break;
		case LONG_OPND:
			if (x->d86_opnd_size == SIZE16)
				(void) strlcat(opnd, dis_REG16[r_m], OPLEN);
			else if (x->d86_opnd_size == SIZE32)
				(void) strlcat(opnd, dis_REG32[r_m], OPLEN);
			else
				(void) strlcat(opnd, dis_REG64[r_m], OPLEN);
			break;
		}
#endif /* DIS_TEXT */
		return;
	}

	/*
	 * if symbolic representation, skip override prefix, if any
	 */
	dtrace_check_override(x, opindex);

	/*
	 * Handle 16 bit memory references first, since they decode
	 * the mode values more simply.
	 * mode 1 is r_m + 8 bit displacement
	 * mode 2 is r_m + 16 bit displacement
	 * mode 0 is just r_m, unless r_m is 6 which is 16 bit disp
	 */
	if (x->d86_addr_size == SIZE16) {
		if ((mode == 0 && r_m == 6) || mode == 2)
			dtrace_imm_opnd(x, WORD_OPND, 2, opindex);
		else if (mode == 1)
			dtrace_imm_opnd(x, BYTE_OPND, 1, opindex);
#ifdef DIS_TEXT
		if (mode == 0 && r_m == 6)
			x->d86_opnd[opindex].d86_mode = MODE_SIGNED;
		else if (mode == 0)
			x->d86_opnd[opindex].d86_mode = MODE_NONE;
		else
			x->d86_opnd[opindex].d86_mode = MODE_OFFSET;
		(void) strlcat(opnd, dis_addr16[mode][r_m], OPLEN);
#endif
		return;
	}

	/*
	 * 32 and 64 bit addressing modes are more complex since they
	 * can involve an SIB (scaled index and base) byte to decode.
	 */
	if (r_m == ESP_REGNO || r_m == ESP_REGNO + 8) {
		have_SIB = 1;
		dtrace_get_SIB(x, &ss, &index, &base);
		if (x->d86_error)
			return;
		if (base != 5 || mode != 0)
			if (x->d86_rex_prefix & REX_B)
				base += 8;
		if (x->d86_rex_prefix & REX_X)
			index += 8;
	} else {
		base = r_m;
	}

	/*
	 * Compute the displacement size and get its bytes
	 */
	dispsize = 0;

	if (mode == 1)
		dispsize = 1;
	else if (mode == 2)
		dispsize = 4;
	else if ((r_m & 7) == EBP_REGNO ||
	    (have_SIB && (base & 7) == EBP_REGNO))
		dispsize = 4;

	if (dispsize > 0) {
		dtrace_imm_opnd(x, dispsize == 4 ? LONG_OPND : BYTE_OPND,
		    dispsize, opindex);
		if (x->d86_error)
			return;
	}

#ifdef DIS_TEXT
	if (dispsize > 0)
		x->d86_opnd[opindex].d86_mode = MODE_OFFSET;

	if (have_SIB == 0) {
		if (x->d86_mode == SIZE32) {
			if (mode == 0)
				(void) strlcat(opnd, dis_addr32_mode0[r_m],
				    OPLEN);
			else
				(void) strlcat(opnd, dis_addr32_mode12[r_m],
				    OPLEN);
		} else {
			if (mode == 0) {
				(void) strlcat(opnd, dis_addr64_mode0[r_m],
				    OPLEN);
				if (r_m == 5) {
					x->d86_opnd[opindex].d86_mode =
					    MODE_RIPREL;
				}
			} else {
				(void) strlcat(opnd, dis_addr64_mode12[r_m],
				    OPLEN);
			}
		}
	} else {
		uint_t need_paren = 0;
		char **regs;
		char **bregs;
		const char *const *sf;
		if (x->d86_mode == SIZE32) /* NOTE this is not addr_size! */
			regs = (char **)dis_REG32;
		else
			regs = (char **)dis_REG64;

		if (x->d86_vsib != 0) {
			if (wbit == YMM_OPND) /* NOTE this is not addr_size! */
				bregs = (char **)dis_YMMREG;
			else
				bregs = (char **)dis_XMMREG;
			sf = dis_vscale_factor;
		} else {
			bregs = regs;
			sf = dis_scale_factor;
		}

		/*
		 * print the base (if any)
		 */
		if (base == EBP_REGNO && mode == 0) {
			if (index != ESP_REGNO || x->d86_vsib != 0) {
				(void) strlcat(opnd, "(", OPLEN);
				need_paren = 1;
			}
		} else {
			(void) strlcat(opnd, "(", OPLEN);
			(void) strlcat(opnd, regs[base], OPLEN);
			need_paren = 1;
		}

		/*
		 * print the index (if any)
		 */
		if (index != ESP_REGNO || x->d86_vsib) {
			(void) strlcat(opnd, ",", OPLEN);
			(void) strlcat(opnd, bregs[index], OPLEN);
			(void) strlcat(opnd, sf[ss], OPLEN);
		} else
			if (need_paren)
				(void) strlcat(opnd, ")", OPLEN);
	}
#endif
}