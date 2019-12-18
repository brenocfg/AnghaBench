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
typedef  int /*<<< orphan*/  valueT ;
typedef  scalar_t__ LITTLENUM_TYPE ;

/* Variables and functions */
 int MAX_LITTLENUMS ; 
 char* _ (char*) ; 
 char* atof_ieee (char*,int,scalar_t__*) ; 
 char* input_line_pointer ; 
 int /*<<< orphan*/  md_number_to_chars (char*,int /*<<< orphan*/ ,int) ; 

char *
md_atof (int type, char *litP, int *sizeP)
{
  int              i;
  int              prec;
  LITTLENUM_TYPE   words [MAX_LITTLENUMS];
  char *           t;

  switch (type)
    {
    case 'f':
    case 'F':
    case 's':
    case 'S':
      prec = 2;
      break;

    case 'd':
    case 'D':
    case 'r':
    case 'R':
      prec = 4;
      break;

    /* FIXME: Some targets allow other format chars for bigger sizes here.  */
    default:
      *sizeP = 0;
      return _("Bad call to md_atof()");
    }

  t = atof_ieee (input_line_pointer, type, words);
  if (t)
    input_line_pointer = t;
  * sizeP = prec * sizeof (LITTLENUM_TYPE);

  for (i = 0; i < prec; i++)
    {
      md_number_to_chars (litP, (valueT) words[i],
			  sizeof (LITTLENUM_TYPE));
      litP += sizeof (LITTLENUM_TYPE);
    }

  return 0;
}