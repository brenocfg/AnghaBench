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
struct ExtInstruction {char flags; char* name; } ;
struct ExtAuxRegister {char* name; unsigned char address; struct ExtAuxRegister* next; } ;
struct TYPE_2__ {char** coreRegisters; char** condCodes; struct ExtAuxRegister* auxRegisters; struct ExtInstruction** instructions; } ;

/* Variables and functions */
#define  EXT_AUX_REGISTER 131 
#define  EXT_COND_CODE 130 
#define  EXT_CORE_REGISTER 129 
#define  EXT_INSTRUCTION 128 
 TYPE_1__ arc_extension_map ; 
 int /*<<< orphan*/  cleanup_ext_map () ; 
 scalar_t__ malloc (int) ; 
 int /*<<< orphan*/  strcpy (char*,char*) ; 
 scalar_t__ xmalloc (int) ; 

int
arcExtMap_add(void *base, unsigned long length)
{
  unsigned char *block = base;
  unsigned char *p = block;

  /* Clean up and reset everything if needed.  */
  cleanup_ext_map();

  while (p && p < (block + length))
    {
      /* p[0] == length of record
	 p[1] == type of record
	 For instructions:
	   p[2]  = opcode
	   p[3]  = minor opcode (if opcode == 3)
	   p[4]  = flags
	   p[5]+ = name
	 For core regs and condition codes:
	   p[2]  = value
	   p[3]+ = name
	 For aux regs:
	   p[2..5] = value
	   p[6]+   = name
	 (value is p[2]<<24|p[3]<<16|p[4]<<8|p[5])  */

      if (p[0] == 0)
	return -1;

      switch (p[1])
	{
	case EXT_INSTRUCTION:
	  {
	    char opcode = p[2];
	    char minor  = p[3];
	    char * insn_name = (char *) xmalloc(( (int)*p-5) * sizeof(char));
	    struct ExtInstruction * insn =
	      (struct ExtInstruction *) xmalloc(sizeof(struct ExtInstruction));

	    if (opcode==3)
	      opcode = 0x1f - 0x10 + minor - 0x09 + 1;
	    else
	      opcode -= 0x10;
	    insn -> flags = (char) *(p+4);
	    strcpy (insn_name, (char *) (p+5));
	    insn -> name = insn_name;
	    arc_extension_map.instructions[(int) opcode] = insn;
	  }
	  break;

	case EXT_CORE_REGISTER:
	  {
	    char * core_name = (char *) xmalloc(((int)*p-3) * sizeof(char));

	    strcpy(core_name, (char *) (p+3));
	    arc_extension_map.coreRegisters[p[2]-32] = core_name;
	  }
	  break;

	case EXT_COND_CODE:
	  {
	    char * cc_name = (char *) xmalloc( ((int)*p-3) * sizeof(char));
	    strcpy(cc_name, (char *) (p+3));
	    arc_extension_map.condCodes[p[2]-16] = cc_name;
	  }
	  break;

	case EXT_AUX_REGISTER:
	  {
	    /* trickier -- need to store linked list to these  */
	    struct ExtAuxRegister *newAuxRegister =
	      (struct ExtAuxRegister *)malloc(sizeof(struct ExtAuxRegister));
	    char * aux_name = (char *) xmalloc ( ((int)*p-6) * sizeof(char));

	    strcpy (aux_name, (char *) (p+6));
	    newAuxRegister->name = aux_name;
	    newAuxRegister->address = p[2]<<24 | p[3]<<16 | p[4]<<8  | p[5];
	    newAuxRegister->next = arc_extension_map.auxRegisters;
	    arc_extension_map.auxRegisters = newAuxRegister;
	  }
	  break;

	default:
	  return -1;

	}
      p += p[0]; /* move to next record  */
    }

  return 0;
}