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
struct TYPE_2__ {unsigned long address; unsigned int last_file_entry; } ;

/* Variables and functions */
#define  DW_LNE_define_file 130 
#define  DW_LNE_end_sequence 129 
#define  DW_LNE_set_address 128 
 char* _ (char*) ; 
 unsigned long byte_get (unsigned char*,unsigned int) ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 unsigned int read_leb128 (unsigned char*,unsigned int*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  reset_state_machine (int) ; 
 TYPE_1__ state_machine_regs ; 
 int /*<<< orphan*/  strlen (char*) ; 
 int /*<<< orphan*/  warn (char*) ; 

__attribute__((used)) static int
process_extended_line_op (unsigned char *data, int is_stmt)
{
  unsigned char op_code;
  unsigned int bytes_read;
  unsigned int len;
  unsigned char *name;
  unsigned long adr;

  len = read_leb128 (data, & bytes_read, 0);
  data += bytes_read;

  if (len == 0)
    {
      warn (_("badly formed extended line op encountered!\n"));
      return bytes_read;
    }

  len += bytes_read;
  op_code = *data++;

  printf (_("  Extended opcode %d: "), op_code);

  switch (op_code)
    {
    case DW_LNE_end_sequence:
      printf (_("End of Sequence\n\n"));
      reset_state_machine (is_stmt);
      break;

    case DW_LNE_set_address:
      adr = byte_get (data, len - bytes_read - 1);
      printf (_("set Address to 0x%lx\n"), adr);
      state_machine_regs.address = adr;
      break;

    case DW_LNE_define_file:
      printf (_("  define new File Table entry\n"));
      printf (_("  Entry\tDir\tTime\tSize\tName\n"));

      printf (_("   %d\t"), ++state_machine_regs.last_file_entry);
      name = data;
      data += strlen ((char *) data) + 1;
      printf (_("%lu\t"), read_leb128 (data, & bytes_read, 0));
      data += bytes_read;
      printf (_("%lu\t"), read_leb128 (data, & bytes_read, 0));
      data += bytes_read;
      printf (_("%lu\t"), read_leb128 (data, & bytes_read, 0));
      printf (_("%s\n\n"), name);
      break;

    default:
      printf (_("UNKNOWN: length %d\n"), len - bytes_read);
      break;
    }

  return len;
}