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
struct field_t {unsigned int lb; int /*<<< orphan*/  sz; int /*<<< orphan*/  name; } ;
typedef  int /*<<< orphan*/  bitstr_t ;

/* Variables and functions */
 int /*<<< orphan*/  BYTE_ALIGN (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  CHECK_BOUND (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int H323_ERROR_NONE ; 
 int /*<<< orphan*/  INC_BITS (int /*<<< orphan*/ *,unsigned int) ; 
 int /*<<< orphan*/  PRINT (char*,int,char*,int /*<<< orphan*/ ) ; 
 int TAB_SIZE ; 
 unsigned int get_bits (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int decode_numstr(bitstr_t *bs, const struct field_t *f,
                         char *base, int level)
{
	unsigned int len;

	PRINT("%*.s%s\n", level * TAB_SIZE, " ", f->name);

	/* 2 <= Range <= 255 */
	len = get_bits(bs, f->sz) + f->lb;

	BYTE_ALIGN(bs);
	INC_BITS(bs, (len << 2));

	CHECK_BOUND(bs, 0);
	return H323_ERROR_NONE;
}