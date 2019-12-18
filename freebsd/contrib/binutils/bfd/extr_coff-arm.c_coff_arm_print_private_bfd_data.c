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
typedef  int /*<<< orphan*/  bfd_boolean ;
typedef  int /*<<< orphan*/  bfd ;
struct TYPE_2__ {int flags; } ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 scalar_t__ APCS_26_FLAG (int /*<<< orphan*/ *) ; 
 scalar_t__ APCS_FLOAT_FLAG (int /*<<< orphan*/ *) ; 
 scalar_t__ APCS_SET (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  BFD_ASSERT (int) ; 
 scalar_t__ INTERWORK_FLAG (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  INTERWORK_SET (int /*<<< orphan*/ *) ; 
 scalar_t__ PIC_FLAG (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  TRUE ; 
 char* _ (char*) ; 
 TYPE_1__* coff_data (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ *,char*,...) ; 
 int /*<<< orphan*/  fputc (char,int /*<<< orphan*/ *) ; 

__attribute__((used)) static bfd_boolean
coff_arm_print_private_bfd_data (bfd * abfd, void * ptr)
{
  FILE * file = (FILE *) ptr;

  BFD_ASSERT (abfd != NULL && ptr != NULL);

  /* xgettext:c-format */
  fprintf (file, _("private flags = %x:"), coff_data (abfd)->flags);

  if (APCS_SET (abfd))
    {
      /* xgettext: APCS is ARM Procedure Call Standard, it should not be translated.  */
      fprintf (file, " [APCS-%d]", APCS_26_FLAG (abfd) ? 26 : 32);

      if (APCS_FLOAT_FLAG (abfd))
	fprintf (file, _(" [floats passed in float registers]"));
      else
	fprintf (file, _(" [floats passed in integer registers]"));

      if (PIC_FLAG (abfd))
	fprintf (file, _(" [position independent]"));
      else
	fprintf (file, _(" [absolute position]"));
    }

  if (! INTERWORK_SET (abfd))
    fprintf (file, _(" [interworking flag not initialised]"));
  else if (INTERWORK_FLAG (abfd))
    fprintf (file, _(" [interworking supported]"));
  else
    fprintf (file, _(" [interworking not supported]"));

  fputc ('\n', file);

  return TRUE;
}