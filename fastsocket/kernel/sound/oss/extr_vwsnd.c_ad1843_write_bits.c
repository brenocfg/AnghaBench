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
typedef  int /*<<< orphan*/  lithium_t ;
struct TYPE_3__ {int nbits; int lo_bit; int /*<<< orphan*/  reg; } ;
typedef  TYPE_1__ ad1843_bitfield_t ;

/* Variables and functions */
 int /*<<< orphan*/  DBGXV (char*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int,int,int) ; 
 int li_read_ad1843_reg (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  li_write_ad1843_reg (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int ad1843_write_bits(lithium_t *lith,
			     const ad1843_bitfield_t *field,
			     int newval)
{
	int w = li_read_ad1843_reg(lith, field->reg);
	int mask = ((1 << field->nbits) - 1) << field->lo_bit;
	int oldval = (w & mask) >> field->lo_bit;
	int newbits = (newval << field->lo_bit) & mask;
	w = (w & ~mask) | newbits;
	(void) li_write_ad1843_reg(lith, field->reg, w);

	DBGXV("ad1843_write_bits(lith=0x%p, field->{%d %d %d}, val=0x%x) "
	      "returns 0x%x\n",
	      lith, field->reg, field->lo_bit, field->nbits, newval,
	      oldval);

	return oldval;
}