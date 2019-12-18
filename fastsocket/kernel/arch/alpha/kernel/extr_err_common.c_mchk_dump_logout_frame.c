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
struct el_common {scalar_t__ sys_offset; scalar_t__ size; scalar_t__ proc_offset; int /*<<< orphan*/  frame_rev; int /*<<< orphan*/  code; scalar_t__ err2; scalar_t__ retry; } ;

/* Variables and functions */
 int /*<<< orphan*/  err_print_prefix ; 
 int /*<<< orphan*/  mchk_dump_mem (void*,scalar_t__,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  printk (char*,int /*<<< orphan*/ ,...) ; 

void
mchk_dump_logout_frame(struct el_common *mchk_header)
{
	printk("%s  -- Frame Header --\n"
	         "    Frame Size:   %d (0x%x) bytes\n"
	         "    Flags:        %s%s\n"
	         "    MCHK Code:    0x%x\n"
	         "    Frame Rev:    %d\n"
	         "    Proc Offset:  0x%08x\n"
	         "    Sys Offset:   0x%08x\n"
  	         "  -- Processor Region --\n",
	       err_print_prefix, 
	       mchk_header->size, mchk_header->size,
	       mchk_header->retry ? "RETRY " : "", 
  	         mchk_header->err2 ? "SECOND_ERR " : "",
	       mchk_header->code,
	       mchk_header->frame_rev,
	       mchk_header->proc_offset,
	       mchk_header->sys_offset);

	mchk_dump_mem((void *)
		      ((unsigned long)mchk_header + mchk_header->proc_offset),
		      mchk_header->sys_offset - mchk_header->proc_offset,
		      NULL);
	
	printk("%s  -- System Region --\n", err_print_prefix);
	mchk_dump_mem((void *)
		      ((unsigned long)mchk_header + mchk_header->sys_offset),
		      mchk_header->size - mchk_header->sys_offset,
		      NULL);
	printk("%s  -- End of Frame --\n", err_print_prefix);
}