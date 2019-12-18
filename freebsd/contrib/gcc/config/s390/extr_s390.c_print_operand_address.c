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
struct s390_address {scalar_t__ base; scalar_t__ indx; scalar_t__ disp; } ;
typedef  int /*<<< orphan*/  rtx ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 size_t REGNO (scalar_t__) ; 
 int /*<<< orphan*/  REGNO_OK_FOR_BASE_P (size_t) ; 
 int /*<<< orphan*/  REGNO_OK_FOR_INDEX_P (size_t) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ *,char*,...) ; 
 int /*<<< orphan*/  output_addr_const (int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  output_operand_lossage (char*) ; 
 char** reg_names ; 
 int /*<<< orphan*/  s390_decompose_address (int /*<<< orphan*/ ,struct s390_address*) ; 

void
print_operand_address (FILE *file, rtx addr)
{
  struct s390_address ad;

  if (!s390_decompose_address (addr, &ad)
      || (ad.base && !REGNO_OK_FOR_BASE_P (REGNO (ad.base)))
      || (ad.indx && !REGNO_OK_FOR_INDEX_P (REGNO (ad.indx))))
    output_operand_lossage ("cannot decompose address");

  if (ad.disp)
    output_addr_const (file, ad.disp);
  else
    fprintf (file, "0");

  if (ad.base && ad.indx)
    fprintf (file, "(%s,%s)", reg_names[REGNO (ad.indx)],
                              reg_names[REGNO (ad.base)]);
  else if (ad.base)
    fprintf (file, "(%s)", reg_names[REGNO (ad.base)]);
}