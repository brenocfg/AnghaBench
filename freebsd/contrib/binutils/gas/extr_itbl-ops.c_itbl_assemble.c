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
struct itbl_entry {int processor; unsigned long value; struct itbl_field* fields; } ;

/* Variables and functions */
 unsigned long apply_range (unsigned long,int /*<<< orphan*/ ) ; 
 unsigned long build_opcode (struct itbl_entry*) ; 
#define  e_addr 132 
#define  e_creg 131 
#define  e_dreg 130 
#define  e_greg 129 
#define  e_immed 128 
 int e_insn ; 
 int e_nprocs ; 
 struct itbl_entry* find_entry_byname (int,int,char*) ; 
 char* itbl_get_field (char**) ; 
 unsigned long strtol (char*,int /*<<< orphan*/ ,int) ; 

unsigned long
itbl_assemble (char *name, char *s)
{
  unsigned long opcode;
  struct itbl_entry *e = NULL;
  struct itbl_field *f;
  char *n;
  int processor;

  if (!name || !*name)
    return 0;			/* error!  must have an opcode name/expr */

  /* find entry in list of instructions for all processors */
  for (processor = 0; processor < e_nprocs; processor++)
    {
      e = find_entry_byname (processor, e_insn, name);
      if (e)
	break;
    }
  if (!e)
    return 0;			/* opcode not in table; invalid instruction */
  opcode = build_opcode (e);

  /* parse opcode's args (if any) */
  for (f = e->fields; f; f = f->next)	/* for each arg, ...  */
    {
      struct itbl_entry *r;
      unsigned long value;
      if (!s || !*s)
	return 0;		/* error - not enough operands */
      n = itbl_get_field (&s);
      /* n should be in form $n or 0xhhh (are symbol names valid?? */
      switch (f->type)
	{
	case e_dreg:
	case e_creg:
	case e_greg:
	  /* Accept either a string name
			 * or '$' followed by the register number */
	  if (*n == '$')
	    {
	      n++;
	      value = strtol (n, 0, 10);
	      /* FIXME! could have "0l"... then what?? */
	      if (value == 0 && *n != '0')
		return 0;	/* error; invalid operand */
	    }
	  else
	    {
	      r = find_entry_byname (e->processor, f->type, n);
	      if (r)
		value = r->value;
	      else
		return 0;	/* error; invalid operand */
	    }
	  break;
	case e_addr:
	  /* use assembler's symbol table to find symbol */
	  /* FIXME!! Do we need this?
				if so, what about relocs??
				my_getExpression (&imm_expr, s);
				return 0;	/-* error; invalid operand *-/
				break;
			*/
	  /* If not a symbol, fall thru to IMMED */
	case e_immed:
	  if (*n == '0' && *(n + 1) == 'x')	/* hex begins 0x...  */
	    {
	      n += 2;
	      value = strtol (n, 0, 16);
	      /* FIXME! could have "0xl"... then what?? */
	    }
	  else
	    {
	      value = strtol (n, 0, 10);
	      /* FIXME! could have "0l"... then what?? */
	      if (value == 0 && *n != '0')
		return 0;	/* error; invalid operand */
	    }
	  break;
	default:
	  return 0;		/* error; invalid field spec */
	}
      opcode |= apply_range (value, f->range);
    }
  if (s && *s)
    return 0;			/* error - too many operands */
  return opcode;		/* done! */
}