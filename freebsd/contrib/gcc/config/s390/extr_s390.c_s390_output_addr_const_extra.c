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
typedef  int /*<<< orphan*/  rtx ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 scalar_t__ GET_CODE (int /*<<< orphan*/ ) ; 
 scalar_t__ UNSPEC ; 
#define  UNSPEC_DTPOFF 138 
#define  UNSPEC_GOT 137 
#define  UNSPEC_GOTENT 136 
#define  UNSPEC_GOTNTPOFF 135 
#define  UNSPEC_GOTOFF 134 
#define  UNSPEC_INDNTPOFF 133 
#define  UNSPEC_NTPOFF 132 
#define  UNSPEC_PLT 131 
#define  UNSPEC_PLTOFF 130 
#define  UNSPEC_TLSGD 129 
#define  UNSPEC_TLSLDM 128 
 int XINT (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  XVECEXP (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int XVECLEN (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  assemble_name (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  get_some_local_dynamic_name () ; 
 int /*<<< orphan*/  output_addr_const (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

bool
s390_output_addr_const_extra (FILE *file, rtx x)
{
  if (GET_CODE (x) == UNSPEC && XVECLEN (x, 0) == 1)
    switch (XINT (x, 1))
      {
      case UNSPEC_GOTENT:
	output_addr_const (file, XVECEXP (x, 0, 0));
	fprintf (file, "@GOTENT");
	return true;
      case UNSPEC_GOT:
	output_addr_const (file, XVECEXP (x, 0, 0));
	fprintf (file, "@GOT");
	return true;
      case UNSPEC_GOTOFF:
	output_addr_const (file, XVECEXP (x, 0, 0));
	fprintf (file, "@GOTOFF");
	return true;
      case UNSPEC_PLT:
	output_addr_const (file, XVECEXP (x, 0, 0));
	fprintf (file, "@PLT");
	return true;
      case UNSPEC_PLTOFF:
	output_addr_const (file, XVECEXP (x, 0, 0));
	fprintf (file, "@PLTOFF");
	return true;
      case UNSPEC_TLSGD:
	output_addr_const (file, XVECEXP (x, 0, 0));
	fprintf (file, "@TLSGD");
	return true;
      case UNSPEC_TLSLDM:
	assemble_name (file, get_some_local_dynamic_name ());
	fprintf (file, "@TLSLDM");
	return true;
      case UNSPEC_DTPOFF:
	output_addr_const (file, XVECEXP (x, 0, 0));
	fprintf (file, "@DTPOFF");
	return true;
      case UNSPEC_NTPOFF:
	output_addr_const (file, XVECEXP (x, 0, 0));
	fprintf (file, "@NTPOFF");
	return true;
      case UNSPEC_GOTNTPOFF:
	output_addr_const (file, XVECEXP (x, 0, 0));
	fprintf (file, "@GOTNTPOFF");
	return true;
      case UNSPEC_INDNTPOFF:
	output_addr_const (file, XVECEXP (x, 0, 0));
	fprintf (file, "@INDNTPOFF");
	return true;
      }

  return false;
}