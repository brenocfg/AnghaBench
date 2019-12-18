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
typedef  int /*<<< orphan*/  bfd ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 char* ASM_C ; 
 char* ASM_GLOBAL ; 
 char* ASM_LONG ; 
 char* ASM_RVA_AFTER ; 
 char* ASM_RVA_BEFORE ; 
 int /*<<< orphan*/  FOPEN_WT ; 
 int /*<<< orphan*/  HOW_BFD_READ_TARGET ; 
 int /*<<< orphan*/  TMP_HEAD_O ; 
 int /*<<< orphan*/  TMP_HEAD_S ; 
 int /*<<< orphan*/  _ (char*) ; 
 int /*<<< orphan*/  assemble_file (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * bfd_openr (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fatal (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fclose (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * fopen (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ *,char*,...) ; 
 char* head_label ; 
 char* imp_name_lab ; 
 int /*<<< orphan*/  no_idata4 ; 
 int /*<<< orphan*/  no_idata5 ; 

__attribute__((used)) static bfd *
make_head (void)
{
  FILE *f = fopen (TMP_HEAD_S, FOPEN_WT);

  if (f == NULL)
    {
      fatal (_("failed to open temporary head file: %s"), TMP_HEAD_S);
      return NULL;
    }

  fprintf (f, "%s IMAGE_IMPORT_DESCRIPTOR\n", ASM_C);
  fprintf (f, "\t.section	.idata$2\n");

  fprintf(f,"\t%s\t%s\n", ASM_GLOBAL,head_label);

  fprintf (f, "%s:\n", head_label);

  fprintf (f, "\t%shname%s\t%sPtr to image import by name list\n",
	   ASM_RVA_BEFORE, ASM_RVA_AFTER, ASM_C);

  fprintf (f, "\t%sthis should be the timestamp, but NT sometimes\n", ASM_C);
  fprintf (f, "\t%sdoesn't load DLLs when this is set.\n", ASM_C);
  fprintf (f, "\t%s\t0\t%s loaded time\n", ASM_LONG, ASM_C);
  fprintf (f, "\t%s\t0\t%s Forwarder chain\n", ASM_LONG, ASM_C);
  fprintf (f, "\t%s__%s_iname%s\t%s imported dll's name\n",
	   ASM_RVA_BEFORE,
	   imp_name_lab,
	   ASM_RVA_AFTER,
	   ASM_C);
  fprintf (f, "\t%sfthunk%s\t%s pointer to firstthunk\n",
	   ASM_RVA_BEFORE,
	   ASM_RVA_AFTER, ASM_C);

  fprintf (f, "%sStuff for compatibility\n", ASM_C);

  if (!no_idata5)
    {
      fprintf (f, "\t.section\t.idata$5\n");
#ifdef DLLTOOL_MX86_64
      fprintf (f,"\t%s\t0\n\t%s\t0\n", ASM_LONG, ASM_LONG); /* NULL terminating list.  */
#else
      fprintf (f,"\t%s\t0\n", ASM_LONG); /* NULL terminating list.  */
#endif
      fprintf (f, "fthunk:\n");
    }

  if (!no_idata4)
    {
      fprintf (f, "\t.section\t.idata$4\n");
      fprintf (f, "\t%s\t0\n", ASM_LONG);
      fprintf (f, "\t.section	.idata$4\n");
      fprintf (f, "hname:\n");
    }

  fclose (f);

  assemble_file (TMP_HEAD_S, TMP_HEAD_O);

  return bfd_openr (TMP_HEAD_O, HOW_BFD_READ_TARGET);
}