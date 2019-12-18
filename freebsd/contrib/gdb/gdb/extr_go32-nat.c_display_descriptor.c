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
struct seg_descr {int limit1; int limit0; int stype; int base0; scalar_t__ present; int /*<<< orphan*/  bit32; int /*<<< orphan*/  base1; int /*<<< orphan*/  base2; scalar_t__ page_granular; } ;
struct gate_descr {int param_count; int /*<<< orphan*/  offset0; int /*<<< orphan*/  offset1; int /*<<< orphan*/  selector; } ;
struct TYPE_2__ {int tss_cs; } ;

/* Variables and functions */
 int _my_cs () ; 
 TYPE_1__ a_tss ; 
 int get_descriptor (unsigned long,int,struct seg_descr*) ; 
 int /*<<< orphan*/  memcpy (struct gate_descr*,struct seg_descr*,int) ; 
 int /*<<< orphan*/  printf_filtered (char*,...) ; 
 int /*<<< orphan*/  printfi_filtered (int,char*) ; 
 scalar_t__ prog_has_started ; 
 int /*<<< orphan*/  puts_filtered (char*) ; 

__attribute__((used)) static void
display_descriptor (unsigned type, unsigned long base_addr, int idx, int force)
{
  struct seg_descr descr;
  struct gate_descr gate;

  /* Get the descriptor from the table.  */
  if (idx == 0 && type == 0)
    puts_filtered ("0x000: null descriptor\n");
  else if (get_descriptor (base_addr, idx, &descr) != -1)
    {
      /* For each type of descriptor table, this has a bit set if the
	 corresponding type of selectors is valid in that table.  */
      static unsigned allowed_descriptors[] = {
	  0xffffdafeL,   /* GDT */
	  0x0000c0e0L,   /* IDT */
	  0xffffdafaL    /* LDT */
      };

      /* If the program hasn't started yet, assume the debuggee will
	 have the same CPL as the debugger.  */
      int cpl = prog_has_started ? (a_tss.tss_cs & 3) : _my_cs () & 3;
      unsigned long limit = (descr.limit1 << 16) | descr.limit0;

      if (descr.present
	  && (allowed_descriptors[type] & (1 << descr.stype)) != 0)
	{
	  printf_filtered ("0x%03x: ",
			   type == 1
			   ? idx : (idx * 8) | (type ? (cpl | 4) : 0));
	  if (descr.page_granular)
	    limit = (limit << 12) | 0xfff; /* big segment: low 12 bit set */
	  if (descr.stype == 1 || descr.stype == 2 || descr.stype == 3
	      || descr.stype == 9 || descr.stype == 11
	      || (descr.stype >= 16 && descr.stype < 32))
	    printf_filtered ("base=0x%02x%02x%04x limit=0x%08lx",
			     descr.base2, descr.base1, descr.base0, limit);

	  switch (descr.stype)
	    {
	      case 1:
	      case 3:
		printf_filtered (" 16-bit TSS  (task %sactive)",
				 descr.stype == 3 ? "" : "in");
		break;
	      case 2:
		puts_filtered (" LDT");
		break;
	      case 4:
		memcpy (&gate, &descr, sizeof gate);
		printf_filtered ("selector=0x%04x  offs=0x%04x%04x",
				 gate.selector, gate.offset1, gate.offset0);
		printf_filtered (" 16-bit Call Gate (params=%d)",
				 gate.param_count);
		break;
	      case 5:
		printf_filtered ("TSS selector=0x%04x", descr.base0);
		printfi_filtered (16, "Task Gate");
		break;
	      case 6:
	      case 7:
		memcpy (&gate, &descr, sizeof gate);
		printf_filtered ("selector=0x%04x  offs=0x%04x%04x",
				 gate.selector, gate.offset1, gate.offset0);
		printf_filtered (" 16-bit %s Gate",
				 descr.stype == 6 ? "Interrupt" : "Trap");
		break;
	      case 9:
	      case 11:
		printf_filtered (" 32-bit TSS (task %sactive)",
				 descr.stype == 3 ? "" : "in");
		break;
	      case 12:
		memcpy (&gate, &descr, sizeof gate);
		printf_filtered ("selector=0x%04x  offs=0x%04x%04x",
				 gate.selector, gate.offset1, gate.offset0);
		printf_filtered (" 32-bit Call Gate (params=%d)",
				 gate.param_count);
		break;
	      case 14:
	      case 15:
		memcpy (&gate, &descr, sizeof gate);
		printf_filtered ("selector=0x%04x  offs=0x%04x%04x",
				 gate.selector, gate.offset1, gate.offset0);
		printf_filtered (" 32-bit %s Gate",
				 descr.stype == 14 ? "Interrupt" : "Trap");
		break;
	      case 16:		/* data segments */
	      case 17:
	      case 18:
	      case 19:
	      case 20:
	      case 21:
	      case 22:
	      case 23:
		printf_filtered (" %s-bit Data (%s Exp-%s%s)",
				 descr.bit32 ? "32" : "16",
				 descr.stype & 2 ? "Read/Write," : "Read-Only, ",
				 descr.stype & 4 ? "down" : "up",
				 descr.stype & 1 ? "" : ", N.Acc");
		break;
	      case 24:		/* code segments */
	      case 25:
	      case 26:
	      case 27:
	      case 28:
	      case 29:
	      case 30:
	      case 31:
		printf_filtered (" %s-bit Code (%s,  %sConf%s)",
				 descr.bit32 ? "32" : "16",
				 descr.stype & 2 ? "Exec/Read" : "Exec-Only",
				 descr.stype & 4 ? "" : "N.",
				 descr.stype & 1 ? "" : ", N.Acc");
		break;
	      default:
		printf_filtered ("Unknown type 0x%02x", descr.stype);
		break;
	    }
	  puts_filtered ("\n");
	}
      else if (force)
	{
	  printf_filtered ("0x%03x: ",
			   type == 1
			   ? idx : (idx * 8) | (type ? (cpl | 4) : 0));
	  if (!descr.present)
	    puts_filtered ("Segment not present\n");
	  else
	    printf_filtered ("Segment type 0x%02x is invalid in this table\n",
			     descr.stype);
	}
    }
  else if (force)
    printf_filtered ("0x%03x: Cannot read this descriptor\n", idx);
}