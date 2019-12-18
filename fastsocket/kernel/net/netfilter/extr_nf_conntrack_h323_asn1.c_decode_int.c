#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct field_t {int sz; int attr; unsigned int lb; int /*<<< orphan*/  offset; int /*<<< orphan*/  name; } ;
struct TYPE_9__ {int cur; } ;
typedef  TYPE_1__ bitstr_t ;

/* Variables and functions */
#define  BYTE 131 
 int /*<<< orphan*/  BYTE_ALIGN (TYPE_1__*) ; 
 int /*<<< orphan*/  CHECK_BOUND (TYPE_1__*,int) ; 
#define  CONS 130 
 int DECODE ; 
 int H323_ERROR_NONE ; 
 int /*<<< orphan*/  INC_BITS (TYPE_1__*,int) ; 
 int /*<<< orphan*/  PRINT (char*,...) ; 
 int TAB_SIZE ; 
#define  UNCO 129 
#define  WORD 128 
 int /*<<< orphan*/  get_bits (TYPE_1__*,int) ; 
 unsigned int get_len (TYPE_1__*) ; 
 unsigned int get_uint (TYPE_1__*,unsigned int) ; 

__attribute__((used)) static int decode_int(bitstr_t *bs, const struct field_t *f,
                      char *base, int level)
{
	unsigned int len;

	PRINT("%*.s%s", level * TAB_SIZE, " ", f->name);

	switch (f->sz) {
	case BYTE:		/* Range == 256 */
		BYTE_ALIGN(bs);
		bs->cur++;
		break;
	case WORD:		/* 257 <= Range <= 64K */
		BYTE_ALIGN(bs);
		bs->cur += 2;
		break;
	case CONS:		/* 64K < Range < 4G */
		len = get_bits(bs, 2) + 1;
		BYTE_ALIGN(bs);
		if (base && (f->attr & DECODE)) {	/* timeToLive */
			unsigned int v = get_uint(bs, len) + f->lb;
			PRINT(" = %u", v);
			*((unsigned int *)(base + f->offset)) = v;
		}
		bs->cur += len;
		break;
	case UNCO:
		BYTE_ALIGN(bs);
		CHECK_BOUND(bs, 2);
		len = get_len(bs);
		bs->cur += len;
		break;
	default:		/* 2 <= Range <= 255 */
		INC_BITS(bs, f->sz);
		break;
	}

	PRINT("\n");

	CHECK_BOUND(bs, 0);
	return H323_ERROR_NONE;
}