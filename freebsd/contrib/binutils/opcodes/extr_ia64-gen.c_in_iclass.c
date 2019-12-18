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
struct iclass {char const* comment; int nsubs; scalar_t__ nxsubs; char const* name; int terminal_resolved; size_t* subs; size_t* xsubs; int note; } ;
struct ia64_opcode {char const* name; scalar_t__* operands; int flags; } ;

/* Variables and functions */
 int CONST_STRNEQ (char const*,char*) ; 
 int IA64_OPCODE_POSTINC ; 
 scalar_t__ IA64_OPND_B2 ; 
 scalar_t__ IA64_OPND_F1 ; 
 scalar_t__ IA64_OPND_F2 ; 
 scalar_t__ IA64_OPND_F3 ; 
 scalar_t__ IA64_OPND_IMM14 ; 
 scalar_t__ IA64_OPND_IMM22 ; 
 scalar_t__ IA64_OPND_IMM8 ; 
 scalar_t__ IA64_OPND_IMM9b ; 
 scalar_t__ IA64_OPND_R1 ; 
 scalar_t__ IA64_OPND_R2 ; 
 scalar_t__ IA64_OPND_R3 ; 
 scalar_t__ IA64_OPND_TGT25c ; 
 int /*<<< orphan*/  _ (char*) ; 
 int debug ; 
 struct iclass** ics ; 
 int in_iclass_mov_x (struct ia64_opcode*,struct iclass*,char const*,char const*) ; 
 int /*<<< orphan*/  printf (char*,char const*,char const*) ; 
 scalar_t__ strcmp (char const*,char*) ; 
 int strlen (char const*) ; 
 scalar_t__ strncmp (char const*,char const*,int) ; 
 char* strstr (char const*,char*) ; 
 int /*<<< orphan*/  warn (int /*<<< orphan*/ ,...) ; 

__attribute__((used)) static int
in_iclass (struct ia64_opcode *idesc, struct iclass *ic, 
	   const char *format, const char *field, int *notep)
{
  int i;
  int resolved = 0;

  if (ic->comment)
    {
      if (CONST_STRNEQ (ic->comment, "Format"))
        {
          /* Assume that the first format seen is the most restrictive, and
             only keep a later one if it looks like it's more restrictive.  */
          if (format)
            {
              if (strlen (ic->comment) < strlen (format))
                {
                  warn (_("most recent format '%s'\nappears more restrictive than '%s'\n"),
			ic->comment, format);
                  format = ic->comment; 
                }
            }
          else
            format = ic->comment;
        }
      else if (CONST_STRNEQ (ic->comment, "Field"))
        {
          if (field)
            warn (_("overlapping field %s->%s\n"),
		  ic->comment, field);
          field = ic->comment;
        }
    }

  /* An insn class matches anything that is the same followed by completers,
     except when the absence and presence of completers constitutes different
     instructions.  */
  if (ic->nsubs == 0 && ic->nxsubs == 0)
    {
      int is_mov = CONST_STRNEQ (idesc->name, "mov");
      int plain_mov = strcmp (idesc->name, "mov") == 0;
      int len = strlen(ic->name);

      resolved = ((strncmp (ic->name, idesc->name, len) == 0)
                  && (idesc->name[len] == '\0' 
                      || idesc->name[len] == '.'));

      /* All break, nop, and hint variations must match exactly.  */
      if (resolved &&
          (strcmp (ic->name, "break") == 0
           || strcmp (ic->name, "nop") == 0
	   || strcmp (ic->name, "hint") == 0))
        resolved = strcmp (ic->name, idesc->name) == 0;

      /* Assume restrictions in the FORMAT/FIELD negate resolution,
         unless specifically allowed by clauses in this block.  */
      if (resolved && field)
        {
          /* Check Field(sf)==sN against opcode sN.  */
          if (strstr(field, "(sf)==") != NULL)
            {
              char *sf;

              if ((sf = strstr (idesc->name, ".s")) != 0)
		resolved = strcmp (sf + 1, strstr (field, "==") + 2) == 0;
            }
          /* Check Field(lftype)==XXX.  */
          else if (strstr (field, "(lftype)") != NULL)
            {
              if (strstr (idesc->name, "fault") != NULL)
                resolved = strstr (field, "fault") != NULL;
              else
                resolved = strstr (field, "fault") == NULL;
            }
          /* Handle Field(ctype)==XXX.  */
          else if (strstr (field, "(ctype)") != NULL)
            {
              if (strstr (idesc->name, "or.andcm"))
                resolved = strstr (field, "or.andcm") != NULL;
              else if (strstr (idesc->name, "and.orcm"))
                resolved = strstr (field, "and.orcm") != NULL;
              else if (strstr (idesc->name, "orcm"))
                resolved = strstr (field, "or orcm") != NULL;
              else if (strstr (idesc->name, "or"))
                resolved = strstr (field, "or orcm") != NULL;
              else if (strstr (idesc->name, "andcm"))
                resolved = strstr (field, "and andcm") != NULL;
              else if (strstr (idesc->name, "and"))
                resolved = strstr (field, "and andcm") != NULL;
              else if (strstr (idesc->name, "unc"))
                resolved = strstr (field, "unc") != NULL;
              else
                resolved = strcmp (field, "Field(ctype)==") == 0;
            }
        }

      if (resolved && format)
        {
          if (CONST_STRNEQ (idesc->name, "dep")
                   && strstr (format, "I13") != NULL)
            resolved = idesc->operands[1] == IA64_OPND_IMM8;
          else if (CONST_STRNEQ (idesc->name, "chk")
                   && strstr (format, "M21") != NULL)
            resolved = idesc->operands[0] == IA64_OPND_F2;
          else if (CONST_STRNEQ (idesc->name, "lfetch"))
            resolved = (strstr (format, "M14 M15") != NULL
                        && (idesc->operands[1] == IA64_OPND_R2
                            || idesc->operands[1] == IA64_OPND_IMM9b));
          else if (CONST_STRNEQ (idesc->name, "br.call")
                   && strstr (format, "B5") != NULL)
            resolved = idesc->operands[1] == IA64_OPND_B2;
          else if (CONST_STRNEQ (idesc->name, "br.call")
                   && strstr (format, "B3") != NULL)
            resolved = idesc->operands[1] == IA64_OPND_TGT25c;
          else if (CONST_STRNEQ (idesc->name, "brp")
                   && strstr (format, "B7") != NULL)
            resolved = idesc->operands[0] == IA64_OPND_B2;
          else if (strcmp (ic->name, "invala") == 0)
            resolved = strcmp (idesc->name, ic->name) == 0;
	  else if (CONST_STRNEQ (idesc->name, "st")
		   && (strstr (format, "M5") != NULL
		       || strstr (format, "M10") != NULL))
	    resolved = idesc->flags & IA64_OPCODE_POSTINC;
	  else if (CONST_STRNEQ (idesc->name, "ld")
		   && (strstr (format, "M2 M3") != NULL
		       || strstr (format, "M12") != NULL
		       || strstr (format, "M7 M8") != NULL))
	    resolved = idesc->flags & IA64_OPCODE_POSTINC;
          else
            resolved = 0;
        }

      /* Misc brl variations ('.cond' is optional); 
         plain brl matches brl.cond.  */
      if (!resolved
          && (strcmp (idesc->name, "brl") == 0
              || CONST_STRNEQ (idesc->name, "brl."))
          && strcmp (ic->name, "brl.cond") == 0)
        {
          resolved = 1;
        }

      /* Misc br variations ('.cond' is optional).  */
      if (!resolved 
          && (strcmp (idesc->name, "br") == 0
              || CONST_STRNEQ (idesc->name, "br."))
          && strcmp (ic->name, "br.cond") == 0)
        {
          if (format)
            resolved = (strstr (format, "B4") != NULL
                        && idesc->operands[0] == IA64_OPND_B2)
              || (strstr (format, "B1") != NULL
                  && idesc->operands[0] == IA64_OPND_TGT25c);
          else
            resolved = 1;
        }

      /* probe variations.  */
      if (!resolved && CONST_STRNEQ (idesc->name, "probe"))
        {
          resolved = strcmp (ic->name, "probe") == 0 
            && !((strstr (idesc->name, "fault") != NULL) 
                 ^ (format && strstr (format, "M40") != NULL));
        }

      /* mov variations.  */
      if (!resolved && is_mov)
        {
          if (plain_mov)
            {
              /* mov alias for fmerge.  */
              if (strcmp (ic->name, "fmerge") == 0)
                {
                  resolved = idesc->operands[0] == IA64_OPND_F1
                    && idesc->operands[1] == IA64_OPND_F3;
                }
              /* mov alias for adds (r3 or imm14).  */
              else if (strcmp (ic->name, "adds") == 0)
                {
                  resolved = (idesc->operands[0] == IA64_OPND_R1
                              && (idesc->operands[1] == IA64_OPND_R3
                                  || (idesc->operands[1] == IA64_OPND_IMM14)));
                }
              /* mov alias for addl.  */
              else if (strcmp (ic->name, "addl") == 0)
                {
                  resolved = idesc->operands[0] == IA64_OPND_R1
                    && idesc->operands[1] == IA64_OPND_IMM22;
                }
            }

          /* Some variants of mov and mov.[im].  */
          if (!resolved && CONST_STRNEQ (ic->name, "mov_"))
	    resolved = in_iclass_mov_x (idesc, ic, format, field);
        }

      /* Keep track of this so we can flag any insn classes which aren't 
         mapped onto at least one real insn.  */
      if (resolved)
	ic->terminal_resolved = 1;
    }
  else for (i = 0; i < ic->nsubs; i++)
    {
      if (in_iclass (idesc, ics[ic->subs[i]], format, field, notep))
        {
          int j;

          for (j = 0; j < ic->nxsubs; j++)
	    if (in_iclass (idesc, ics[ic->xsubs[j]], NULL, NULL, NULL))
	      return 0;

          if (debug > 1)
            printf ("%s is in IC %s\n", idesc->name, ic->name);

          resolved = 1;
          break;
        }
    }
  
  /* If it's in this IC, add the IC note (if any) to the insn.  */
  if (resolved)
    {
      if (ic->note && notep)
        {
          if (*notep && *notep != ic->note)
	    warn (_("overwriting note %d with note %d (IC:%s)\n"),
		  *notep, ic->note, ic->name);

          *notep = ic->note;
        }
    }

  return resolved;
}