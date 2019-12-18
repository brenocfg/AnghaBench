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
struct disassemble_info {unsigned int octets_per_byte; unsigned int buffer_length; unsigned int buffer_vma; scalar_t__ buffer; } ;
typedef  unsigned int bfd_vma ;
typedef  int /*<<< orphan*/  bfd_byte ;

/* Variables and functions */
 int EIO ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,scalar_t__,unsigned int) ; 

int
buffer_read_memory (bfd_vma memaddr,
		    bfd_byte *myaddr,
		    unsigned int length,
		    struct disassemble_info *info)
{
  unsigned int opb = info->octets_per_byte;
  unsigned int end_addr_offset = length / opb;
  unsigned int max_addr_offset = info->buffer_length / opb; 
  unsigned int octets = (memaddr - info->buffer_vma) * opb;

  if (memaddr < info->buffer_vma
      || memaddr - info->buffer_vma + end_addr_offset > max_addr_offset)
    /* Out of bounds.  Use EIO because GDB uses it.  */
    return EIO;
  memcpy (myaddr, info->buffer + octets, length);

  return 0;
}