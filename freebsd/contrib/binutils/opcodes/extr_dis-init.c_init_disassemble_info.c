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
struct disassemble_info {int octets_per_byte; void* display_endian; int /*<<< orphan*/  symbol_is_valid; int /*<<< orphan*/  symbol_at_address_func; int /*<<< orphan*/  print_address_func; int /*<<< orphan*/  memory_error_func; int /*<<< orphan*/  read_memory_func; void* stream; int /*<<< orphan*/  fprintf_func; void* endian; int /*<<< orphan*/  arch; int /*<<< orphan*/  flavour; } ;
typedef  int /*<<< orphan*/  fprintf_ftype ;

/* Variables and functions */
 void* BFD_ENDIAN_UNKNOWN ; 
 int /*<<< orphan*/  bfd_arch_unknown ; 
 int /*<<< orphan*/  bfd_target_unknown_flavour ; 
 int /*<<< orphan*/  buffer_read_memory ; 
 int /*<<< orphan*/  generic_print_address ; 
 int /*<<< orphan*/  generic_symbol_at_address ; 
 int /*<<< orphan*/  generic_symbol_is_valid ; 
 int /*<<< orphan*/  memset (struct disassemble_info*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  perror_memory ; 

void
init_disassemble_info (struct disassemble_info *info, void *stream,
		       fprintf_ftype fprintf_func)
{
  memset (info, 0, sizeof (*info));

  info->flavour = bfd_target_unknown_flavour;
  info->arch = bfd_arch_unknown;
  info->endian = BFD_ENDIAN_UNKNOWN;
  info->octets_per_byte = 1;
  info->fprintf_func = fprintf_func;
  info->stream = stream;
  info->read_memory_func = buffer_read_memory;
  info->memory_error_func = perror_memory;
  info->print_address_func = generic_print_address;
  info->symbol_at_address_func = generic_symbol_at_address;
  info->symbol_is_valid = generic_symbol_is_valid;
  info->display_endian = BFD_ENDIAN_UNKNOWN;
}