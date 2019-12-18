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
 int /*<<< orphan*/  TARGET_64BIT ; 
 scalar_t__ UNSPEC ; 
#define  UNSPEC_DTPOFF 133 
#define  UNSPEC_GOTNTPOFF 132 
#define  UNSPEC_GOTTPOFF 131 
#define  UNSPEC_INDNTPOFF 130 
#define  UNSPEC_NTPOFF 129 
#define  UNSPEC_TPOFF 128 
 int XINT (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  XVECEXP (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fputs (char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  output_addr_const (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

bool
output_addr_const_extra (FILE *file, rtx x)
{
  rtx op;

  if (GET_CODE (x) != UNSPEC)
    return false;

  op = XVECEXP (x, 0, 0);
  switch (XINT (x, 1))
    {
    case UNSPEC_GOTTPOFF:
      output_addr_const (file, op);
      /* FIXME: This might be @TPOFF in Sun ld.  */
      fputs ("@GOTTPOFF", file);
      break;
    case UNSPEC_TPOFF:
      output_addr_const (file, op);
      fputs ("@TPOFF", file);
      break;
    case UNSPEC_NTPOFF:
      output_addr_const (file, op);
      if (TARGET_64BIT)
	fputs ("@TPOFF", file);
      else
	fputs ("@NTPOFF", file);
      break;
    case UNSPEC_DTPOFF:
      output_addr_const (file, op);
      fputs ("@DTPOFF", file);
      break;
    case UNSPEC_GOTNTPOFF:
      output_addr_const (file, op);
      if (TARGET_64BIT)
	fputs ("@GOTTPOFF(%rip)", file);
      else
	fputs ("@GOTNTPOFF", file);
      break;
    case UNSPEC_INDNTPOFF:
      output_addr_const (file, op);
      fputs ("@INDNTPOFF", file);
      break;

    default:
      return false;
    }

  return true;
}