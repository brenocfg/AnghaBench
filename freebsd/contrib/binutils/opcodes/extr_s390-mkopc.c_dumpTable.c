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
struct TYPE_2__ {char* mnemonic; char* opcode; int no_nibbles; char* format; int mode_bits; int min_cpu; } ;

/* Variables and functions */
 char* file_header ; 
 int no_ops ; 
 TYPE_1__* op_array ; 
 int /*<<< orphan*/  printf (char*,...) ; 

__attribute__((used)) static void
dumpTable (void)
{
  char *str;
  int  ix;

  /*  Write hash table entries (slots).  */
  printf (file_header);

  for (ix = 0; ix < no_ops; ix++)
    {
      printf ("  { \"%s\", ", op_array[ix].mnemonic);
      for (str = op_array[ix].opcode; *str != 0; str++)
	if (*str == '?')
	  *str = '0';
      printf ("OP%i(0x%sLL), ", 
	      op_array[ix].no_nibbles*4, op_array[ix].opcode);
      printf ("MASK_%s, INSTR_%s, ",
	      op_array[ix].format, op_array[ix].format);
      printf ("%i, ", op_array[ix].mode_bits);
      printf ("%i}", op_array[ix].min_cpu);
      if (ix < no_ops-1)
	printf (",\n");
      else
	printf ("\n");
    }
  printf ("};\n\n");
  printf ("const int s390_num_opcodes =\n");
  printf ("  sizeof (s390_opcodes) / sizeof (s390_opcodes[0]);\n\n");
}