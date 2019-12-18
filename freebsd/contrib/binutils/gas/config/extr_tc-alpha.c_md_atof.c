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
typedef  int /*<<< orphan*/  LITTLENUM_TYPE ;

/* Variables and functions */
 int MAX_LITTLENUMS ; 
 char* _ (char*) ; 
 char* atof_ieee (char*,int,int /*<<< orphan*/ *) ; 
 char* input_line_pointer ; 
 int /*<<< orphan*/  md_number_to_chars (char*,long,int) ; 
 char* vax_md_atof (int,char*,int*) ; 

char *
md_atof (int type, char *litP, int *sizeP)
{
  int prec;
  LITTLENUM_TYPE words[MAX_LITTLENUMS];
  LITTLENUM_TYPE *wordP;
  char *t;

  switch (type)
    {
      /* VAX floats.  */
    case 'G':
      /* VAX md_atof doesn't like "G" for some reason.  */
      type = 'g';
    case 'F':
    case 'D':
      return vax_md_atof (type, litP, sizeP);

      /* IEEE floats.  */
    case 'f':
      prec = 2;
      break;

    case 'd':
      prec = 4;
      break;

    case 'x':
    case 'X':
      prec = 6;
      break;

    case 'p':
    case 'P':
      prec = 6;
      break;

    default:
      *sizeP = 0;
      return _("Bad call to MD_ATOF()");
    }
  t = atof_ieee (input_line_pointer, type, words);
  if (t)
    input_line_pointer = t;
  *sizeP = prec * sizeof (LITTLENUM_TYPE);

  for (wordP = words + prec - 1; prec--;)
    {
      md_number_to_chars (litP, (long) (*wordP--), sizeof (LITTLENUM_TYPE));
      litP += sizeof (LITTLENUM_TYPE);
    }

  return 0;
}