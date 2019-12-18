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
struct operand_alternative {char const* constraint; int matches; int matched; int anything_ok; int reject; int earlyclobber; int memory_ok; int decmem_ok; int incmem_ok; int nonoffmem_ok; int offmem_ok; int is_address; void* cl; } ;
struct TYPE_2__ {int n_operands; int n_alternatives; char** constraints; } ;

/* Variables and functions */
 int /*<<< orphan*/  ADDRESS ; 
 int /*<<< orphan*/  CONSTRAINT_LEN (char,char const*) ; 
 int /*<<< orphan*/  EXTRA_ADDRESS_CONSTRAINT (char,char const*) ; 
 int /*<<< orphan*/  EXTRA_MEMORY_CONSTRAINT (char,char const*) ; 
 scalar_t__ GENERAL_REGS ; 
 void* NO_REGS ; 
 scalar_t__ REG_CLASS_FROM_CONSTRAINT (unsigned char,char const*) ; 
 int /*<<< orphan*/  SCRATCH ; 
 int /*<<< orphan*/  VOIDmode ; 
 scalar_t__ base_reg_class (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (struct operand_alternative*,int /*<<< orphan*/ ,int) ; 
 TYPE_1__ recog_data ; 
 struct operand_alternative** recog_op_alt ; 
 void*** reg_class_subunion ; 
 int strtoul (char const*,char**,int) ; 

void
preprocess_constraints (void)
{
  int i;

  for (i = 0; i < recog_data.n_operands; i++)
    memset (recog_op_alt[i], 0, (recog_data.n_alternatives
				 * sizeof (struct operand_alternative)));

  for (i = 0; i < recog_data.n_operands; i++)
    {
      int j;
      struct operand_alternative *op_alt;
      const char *p = recog_data.constraints[i];

      op_alt = recog_op_alt[i];

      for (j = 0; j < recog_data.n_alternatives; j++)
	{
	  op_alt[j].cl = NO_REGS;
	  op_alt[j].constraint = p;
	  op_alt[j].matches = -1;
	  op_alt[j].matched = -1;

	  if (*p == '\0' || *p == ',')
	    {
	      op_alt[j].anything_ok = 1;
	      continue;
	    }

	  for (;;)
	    {
	      char c = *p;
	      if (c == '#')
		do
		  c = *++p;
		while (c != ',' && c != '\0');
	      if (c == ',' || c == '\0')
		{
		  p++;
		  break;
		}

	      switch (c)
		{
		case '=': case '+': case '*': case '%':
		case 'E': case 'F': case 'G': case 'H':
		case 's': case 'i': case 'n':
		case 'I': case 'J': case 'K': case 'L':
		case 'M': case 'N': case 'O': case 'P':
		  /* These don't say anything we care about.  */
		  break;

		case '?':
		  op_alt[j].reject += 6;
		  break;
		case '!':
		  op_alt[j].reject += 600;
		  break;
		case '&':
		  op_alt[j].earlyclobber = 1;
		  break;

		case '0': case '1': case '2': case '3': case '4':
		case '5': case '6': case '7': case '8': case '9':
		  {
		    char *end;
		    op_alt[j].matches = strtoul (p, &end, 10);
		    recog_op_alt[op_alt[j].matches][j].matched = i;
		    p = end;
		  }
		  continue;

		case 'm':
		  op_alt[j].memory_ok = 1;
		  break;
		case '<':
		  op_alt[j].decmem_ok = 1;
		  break;
		case '>':
		  op_alt[j].incmem_ok = 1;
		  break;
		case 'V':
		  op_alt[j].nonoffmem_ok = 1;
		  break;
		case 'o':
		  op_alt[j].offmem_ok = 1;
		  break;
		case 'X':
		  op_alt[j].anything_ok = 1;
		  break;

		case 'p':
		  op_alt[j].is_address = 1;
		  op_alt[j].cl = reg_class_subunion[(int) op_alt[j].cl]
		      [(int) base_reg_class (VOIDmode, ADDRESS, SCRATCH)];
		  break;

		case 'g':
		case 'r':
		  op_alt[j].cl =
		   reg_class_subunion[(int) op_alt[j].cl][(int) GENERAL_REGS];
		  break;

		default:
		  if (EXTRA_MEMORY_CONSTRAINT (c, p))
		    {
		      op_alt[j].memory_ok = 1;
		      break;
		    }
		  if (EXTRA_ADDRESS_CONSTRAINT (c, p))
		    {
		      op_alt[j].is_address = 1;
		      op_alt[j].cl
			= (reg_class_subunion
			   [(int) op_alt[j].cl]
			   [(int) base_reg_class (VOIDmode, ADDRESS,
						  SCRATCH)]);
		      break;
		    }

		  op_alt[j].cl
		    = (reg_class_subunion
		       [(int) op_alt[j].cl]
		       [(int) REG_CLASS_FROM_CONSTRAINT ((unsigned char) c, p)]);
		  break;
		}
	      p += CONSTRAINT_LEN (c, p);
	    }
	}
    }
}