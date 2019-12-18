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
struct mips_address_info {int type; int /*<<< orphan*/  reg; int /*<<< orphan*/  offset; } ;
typedef  int /*<<< orphan*/  rtx ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
#define  ADDRESS_CONST_INT 131 
#define  ADDRESS_LO_SUM 130 
#define  ADDRESS_REG 129 
#define  ADDRESS_SYMBOLIC 128 
 size_t REGNO (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ *,char*,char*) ; 
 int /*<<< orphan*/  gcc_unreachable () ; 
 scalar_t__ mips_classify_address (struct mips_address_info*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  output_addr_const (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  print_operand (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char) ; 
 char** reg_names ; 
 int /*<<< orphan*/  word_mode ; 

void
print_operand_address (FILE *file, rtx x)
{
  struct mips_address_info addr;

  if (mips_classify_address (&addr, x, word_mode, true))
    switch (addr.type)
      {
      case ADDRESS_REG:
	print_operand (file, addr.offset, 0);
	fprintf (file, "(%s)", reg_names[REGNO (addr.reg)]);
	return;

      case ADDRESS_LO_SUM:
	print_operand (file, addr.offset, 'R');
	fprintf (file, "(%s)", reg_names[REGNO (addr.reg)]);
	return;

      case ADDRESS_CONST_INT:
	output_addr_const (file, x);
	fprintf (file, "(%s)", reg_names[0]);
	return;

      case ADDRESS_SYMBOLIC:
	output_addr_const (file, x);
	return;
      }
  gcc_unreachable ();
}