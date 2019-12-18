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
struct itbl_field {int type; int /*<<< orphan*/  range; struct itbl_field* next; } ;
struct itbl_entry {char* name; int /*<<< orphan*/  processor; struct itbl_field* fields; } ;
typedef  int /*<<< orphan*/  e_processor ;

/* Variables and functions */
 int /*<<< orphan*/  ITBL_DECODE_PNUM (unsigned long) ; 
 int /*<<< orphan*/  ITBL_IS_INSN (unsigned long) ; 
#define  e_addr 132 
#define  e_creg 131 
#define  e_dreg 130 
#define  e_greg 129 
#define  e_immed 128 
 int e_insn ; 
 unsigned long extract_range (unsigned long,int /*<<< orphan*/ ) ; 
 struct itbl_entry* find_entry_byval (int /*<<< orphan*/ ,int,unsigned long,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  get_processor (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sprintf (char*,char*,char*,unsigned long) ; 
 int /*<<< orphan*/  strcat (char*,char*) ; 
 int /*<<< orphan*/  strcpy (char*,char*) ; 

int
itbl_disassemble (char *s, unsigned long insn)
{
  e_processor processor;
  struct itbl_entry *e;
  struct itbl_field *f;

  if (!ITBL_IS_INSN (insn))
    return 0;			/* error */
  processor = get_processor (ITBL_DECODE_PNUM (insn));

  /* find entry in list */
  e = find_entry_byval (processor, e_insn, insn, 0);
  if (!e)
    return 0;			/* opcode not in table; invalid instruction */
  strcpy (s, e->name);

  /* Parse insn's args (if any).  */
  for (f = e->fields; f; f = f->next)	/* for each arg, ...  */
    {
      struct itbl_entry *r;
      unsigned long value;

      if (f == e->fields)	/* First operand is preceded by tab.  */
	strcat (s, "\t");
      else			/* ','s separate following operands.  */
	strcat (s, ",");
      value = extract_range (insn, f->range);
      /* n should be in form $n or 0xhhh (are symbol names valid?? */
      switch (f->type)
	{
	case e_dreg:
	case e_creg:
	case e_greg:
	  /* Accept either a string name
	     or '$' followed by the register number.  */
	  r = find_entry_byval (e->processor, f->type, value, &f->range);
	  if (r)
	    strcat (s, r->name);
	  else
	    sprintf (s, "%s$%lu", s, value);
	  break;
	case e_addr:
	  /* Use assembler's symbol table to find symbol.  */
	  /* FIXME!! Do we need this?  If so, what about relocs??  */
	  /* If not a symbol, fall through to IMMED.  */
	case e_immed:
	  sprintf (s, "%s0x%lx", s, value);
	  break;
	default:
	  return 0;		/* error; invalid field spec */
	}
    }
  return 1;			/* Done!  */
}