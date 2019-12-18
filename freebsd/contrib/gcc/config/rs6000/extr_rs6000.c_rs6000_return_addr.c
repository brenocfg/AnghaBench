#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  rtx ;
struct TYPE_4__ {TYPE_1__* machine; } ;
struct TYPE_3__ {int ra_needs_full_frame; int ra_need_lr; } ;

/* Variables and functions */
 scalar_t__ ABI_AIX ; 
 scalar_t__ DEFAULT_ABI ; 
 int /*<<< orphan*/  LINK_REGISTER_REGNUM ; 
 int /*<<< orphan*/  Pmode ; 
 int /*<<< orphan*/  RETURN_ADDRESS_OFFSET ; 
 TYPE_2__* cfun ; 
 int /*<<< orphan*/  copy_to_reg (int /*<<< orphan*/ ) ; 
 scalar_t__ flag_pic ; 
 int /*<<< orphan*/  gen_rtx_MEM (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  get_hard_reg_initial_val (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memory_address (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  plus_constant (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

rtx
rs6000_return_addr (int count, rtx frame)
{
  /* Currently we don't optimize very well between prolog and body
     code and for PIC code the code can be actually quite bad, so
     don't try to be too clever here.  */
  if (count != 0 || (DEFAULT_ABI != ABI_AIX && flag_pic))
    {
      cfun->machine->ra_needs_full_frame = 1;

      return
	gen_rtx_MEM
	  (Pmode,
	   memory_address
	   (Pmode,
	    plus_constant (copy_to_reg
			   (gen_rtx_MEM (Pmode,
					 memory_address (Pmode, frame))),
			   RETURN_ADDRESS_OFFSET)));
    }

  cfun->machine->ra_need_lr = 1;
  return get_hard_reg_initial_val (Pmode, LINK_REGISTER_REGNUM);
}