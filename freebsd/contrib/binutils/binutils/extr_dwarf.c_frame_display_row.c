#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int ncols; int* col_type; int ra; int cfa_reg; int* col_offset; int /*<<< orphan*/  cfa_offset; scalar_t__ cfa_exp; int /*<<< orphan*/  pc_begin; } ;
typedef  TYPE_1__ Frame_Chunk ;

/* Variables and functions */
#define  DW_CFA_expression 134 
#define  DW_CFA_offset 133 
#define  DW_CFA_register 132 
#define  DW_CFA_same_value 131 
#define  DW_CFA_undefined 130 
 int DW_CFA_unreferenced ; 
#define  DW_CFA_val_expression 129 
#define  DW_CFA_val_offset 128 
 int /*<<< orphan*/  printf (char*,...) ; 
 int /*<<< orphan*/  sprintf (char*,char*,int,...) ; 
 int /*<<< orphan*/  strcpy (char*,char*) ; 

__attribute__((used)) static void
frame_display_row (Frame_Chunk *fc, int *need_col_headers, int *max_regs)
{
  int r;
  char tmp[100];

  if (*max_regs < fc->ncols)
    *max_regs = fc->ncols;

  if (*need_col_headers)
    {
      *need_col_headers = 0;

      printf ("   LOC   CFA      ");

      for (r = 0; r < *max_regs; r++)
	if (fc->col_type[r] != DW_CFA_unreferenced)
	  {
	    if (r == fc->ra)
	      printf ("ra   ");
	    else
	      printf ("r%-4d", r);
	  }

      printf ("\n");
    }

  printf ("%08lx ", fc->pc_begin);
  if (fc->cfa_exp)
    strcpy (tmp, "exp");
  else
    sprintf (tmp, "r%d%+d", fc->cfa_reg, fc->cfa_offset);
  printf ("%-8s ", tmp);

  for (r = 0; r < fc->ncols; r++)
    {
      if (fc->col_type[r] != DW_CFA_unreferenced)
	{
	  switch (fc->col_type[r])
	    {
	    case DW_CFA_undefined:
	      strcpy (tmp, "u");
	      break;
	    case DW_CFA_same_value:
	      strcpy (tmp, "s");
	      break;
	    case DW_CFA_offset:
	      sprintf (tmp, "c%+d", fc->col_offset[r]);
	      break;
	    case DW_CFA_val_offset:
	      sprintf (tmp, "v%+d", fc->col_offset[r]);
	      break;
	    case DW_CFA_register:
	      sprintf (tmp, "r%d", fc->col_offset[r]);
	      break;
	    case DW_CFA_expression:
	      strcpy (tmp, "exp");
	      break;
	    case DW_CFA_val_expression:
	      strcpy (tmp, "vexp");
	      break;
	    default:
	      strcpy (tmp, "n/a");
	      break;
	    }
	  printf ("%-5s", tmp);
	}
    }
  printf ("\n");
}