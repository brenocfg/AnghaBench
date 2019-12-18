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
struct operand_data {scalar_t__ index; struct operand_data* next; } ;
struct data {int n_operands; scalar_t__ operand_number; struct operand_data* operand; } ;

/* Variables and functions */
 scalar_t__ compare_operands (struct operand_data*,struct operand_data*) ; 
 scalar_t__ next_operand_number ; 
 struct operand_data* odata ; 
 struct operand_data** odata_end ; 

__attribute__((used)) static void
place_operands (struct data *d)
{
  struct operand_data *od, *od2;
  int i;

  if (d->n_operands == 0)
    {
      d->operand_number = 0;
      return;
    }

  /* Brute force substring search.  */
  for (od = odata, i = 0; od; od = od->next, i = 0)
    if (compare_operands (od, &d->operand[0]))
      {
	od2 = od->next;
	i = 1;
	while (1)
	  {
	    if (i == d->n_operands)
	      goto full_match;
	    if (od2 == NULL)
	      goto partial_match;
	    if (! compare_operands (od2, &d->operand[i]))
	      break;
	    ++i, od2 = od2->next;
	  }
      }

  /* Either partial match at the end of the list, or no match.  In either
     case, we tack on what operands are remaining to the end of the list.  */
 partial_match:
  d->operand_number = next_operand_number - i;
  for (; i < d->n_operands; ++i)
    {
      od2 = &d->operand[i];
      *odata_end = od2;
      odata_end = &od2->next;
      od2->index = next_operand_number++;
    }
  *odata_end = NULL;
  return;

 full_match:
  d->operand_number = od->index;
  return;
}