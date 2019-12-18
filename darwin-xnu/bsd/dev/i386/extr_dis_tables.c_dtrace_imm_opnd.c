#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ uint_t ;
typedef  int uint64_t ;
struct TYPE_5__ {scalar_t__ d86_numopnds; int d86_error; int (* d86_get_byte ) (int /*<<< orphan*/ ) ;int* d86_bytes; size_t d86_len; int d86_imm_bytes; TYPE_1__* d86_opnd; int /*<<< orphan*/  d86_data; int /*<<< orphan*/  d86_opnd_size; } ;
typedef  TYPE_2__ dis86_t ;
struct TYPE_4__ {int d86_value; int d86_value_size; int /*<<< orphan*/  d86_mode; } ;

/* Variables and functions */
#define  BYTE_OPND 137 
#define  CONTROL_OPND 136 
#define  DEBUG_OPND 135 
#define  LONG_OPND 134 
#define  MM_OPND 133 
 int /*<<< orphan*/  MODE_SIGNED ; 
#define  SEG_OPND 132 
 int /*<<< orphan*/  SIZE16 ; 
 int /*<<< orphan*/  SIZE32 ; 
#define  TEST_OPND 131 
#define  WORD_OPND 130 
#define  XMM_OPND 129 
#define  YMM_OPND 128 
 int stub1 (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
dtrace_imm_opnd(dis86_t *x, int wbit, int size, int opindex)
{
	int i;
	int byte;
	int valsize = 0;

	if (x->d86_numopnds < (uint_t)opindex + 1)
		x->d86_numopnds = (uint_t)opindex + 1;

	switch (wbit) {
	case BYTE_OPND:
		valsize = 1;
		break;
	case LONG_OPND:
		if (x->d86_opnd_size == SIZE16)
			valsize = 2;
		else if (x->d86_opnd_size == SIZE32)
			valsize = 4;
		else
			valsize = 8;
		break;
	case MM_OPND:
	case XMM_OPND:
	case YMM_OPND:
	case SEG_OPND:
	case CONTROL_OPND:
	case DEBUG_OPND:
	case TEST_OPND:
		valsize = size;
		break;
	case WORD_OPND:
		valsize = 2;
		break;
	}
	if (valsize < size)
		valsize = size;

	if (x->d86_error)
		return;
	x->d86_opnd[opindex].d86_value = 0;
	for (i = 0; i < size; ++i) {
		byte = x->d86_get_byte(x->d86_data);
		if (byte < 0) {
			x->d86_error = 1;
			return;
		}
		x->d86_bytes[x->d86_len++] = byte;
		x->d86_opnd[opindex].d86_value |= (uint64_t)byte << (i * 8);
	}
	/* Do sign extension */
	if (x->d86_bytes[x->d86_len - 1] & 0x80) {
		for (; i < (int)sizeof (uint64_t); i++)
			x->d86_opnd[opindex].d86_value |=
			    (uint64_t)0xff << (i * 8);
	}
#ifdef DIS_TEXT
	x->d86_opnd[opindex].d86_mode = MODE_SIGNED;
	x->d86_opnd[opindex].d86_value_size = valsize;
	x->d86_imm_bytes += size;
#endif
}