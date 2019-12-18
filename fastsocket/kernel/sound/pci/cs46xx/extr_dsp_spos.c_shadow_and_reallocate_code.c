#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct snd_cs46xx {struct dsp_spos_instance* dsp_spos_instance; } ;
struct TYPE_2__ {int offset; int* data; int /*<<< orphan*/  size; } ;
struct dsp_spos_instance {TYPE_1__ code; } ;

/* Variables and functions */
 unsigned int ARRAY_SIZE (int*) ; 
 int EINVAL ; 
 int WIDE_INSTR_MASK ; 
 int WIDE_LADD_INSTR_MASK ; 
 scalar_t__ snd_BUG_ON (int) ; 
 int /*<<< orphan*/  snd_printdd (char*,...) ; 
 int* wide_opcodes ; 

__attribute__((used)) static int shadow_and_reallocate_code (struct snd_cs46xx * chip, u32 * data, u32 size,
				       u32 overlay_begin_address)
{
	unsigned int i = 0, j, nreallocated = 0;
	u32 hival,loval,address;
	u32 mop_operands,mop_type,wide_op;
	struct dsp_spos_instance * ins = chip->dsp_spos_instance;

	if (snd_BUG_ON(size %2))
		return -EINVAL;
  
	while (i < size) {
		loval = data[i++];
		hival = data[i++];

		if (ins->code.offset > 0) {
			mop_operands = (hival >> 6) & 0x03fff;
			mop_type = mop_operands >> 10;
      
			/* check for wide type instruction */
			if (mop_type == 0 &&
			    (mop_operands & WIDE_LADD_INSTR_MASK) == 0 &&
			    (mop_operands & WIDE_INSTR_MASK) != 0) {
				wide_op = loval & 0x7f;
				for (j = 0;j < ARRAY_SIZE(wide_opcodes); ++j) {
					if (wide_opcodes[j] == wide_op) {
						/* need to reallocate instruction */
						address  = (hival & 0x00FFF) << 5;
						address |=  loval >> 15;
            
						snd_printdd("handle_wideop[1]: %05x:%05x addr %04x\n",hival,loval,address);
            
						if ( !(address & 0x8000) ) {
							address += (ins->code.offset / 2) - overlay_begin_address;
						} else {
							snd_printdd("handle_wideop[1]: ROM symbol not reallocated\n");
						}
            
						hival &= 0xFF000;
						loval &= 0x07FFF;
            
						hival |= ( (address >> 5)  & 0x00FFF);
						loval |= ( (address << 15) & 0xF8000);
            
						address  = (hival & 0x00FFF) << 5;
						address |=  loval >> 15;
            
						snd_printdd("handle_wideop:[2] %05x:%05x addr %04x\n",hival,loval,address);            
						nreallocated ++;
					} /* wide_opcodes[j] == wide_op */
				} /* for */
			} /* mod_type == 0 ... */
		} /* ins->code.offset > 0 */

		ins->code.data[ins->code.size++] = loval;
		ins->code.data[ins->code.size++] = hival;
	}

	snd_printdd("dsp_spos: %d instructions reallocated\n",nreallocated);
	return nreallocated;
}