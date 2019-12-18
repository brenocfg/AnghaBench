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
struct disassemble_info {int (* read_memory_func ) (int,int /*<<< orphan*/ *,int,struct disassemble_info*) ;int /*<<< orphan*/  (* memory_error_func ) (int,int,struct disassemble_info*) ;scalar_t__ private_data; } ;
struct dis_private {int insn_start; int /*<<< orphan*/ * max_fetched; int /*<<< orphan*/  bailout; int /*<<< orphan*/ * the_buffer; } ;
typedef  int bfd_vma ;
typedef  int /*<<< orphan*/  bfd_byte ;

/* Variables and functions */
 int MAX_MNEM_SIZE ; 
 int /*<<< orphan*/  longjmp (int /*<<< orphan*/ ,int) ; 
 int stub1 (int,int /*<<< orphan*/ *,int,struct disassemble_info*) ; 
 int /*<<< orphan*/  stub2 (int,int,struct disassemble_info*) ; 

__attribute__((used)) static int
fetch_data (struct disassemble_info *info, bfd_byte *addr)
{
  int status;
  struct dis_private *priv = (struct dis_private *) info->private_data;
  bfd_vma start = priv->insn_start + (priv->max_fetched - priv->the_buffer);

  if (addr <= priv->the_buffer + MAX_MNEM_SIZE)
    status = (*info->read_memory_func) (start,
					priv->max_fetched,
					addr - priv->max_fetched,
					info);
  else
    status = -1;
  if (status != 0)
    {
      /* If we did manage to read at least one byte, then
	 print_insn_i386 will do something sensible.  Otherwise, print
	 an error.  We do that here because this is where we know
	 STATUS.  */
      if (priv->max_fetched == priv->the_buffer)
	(*info->memory_error_func) (status, start, info);
      longjmp (priv->bailout, 1);
    }
  else
    priv->max_fetched = addr;
  return 1;
}