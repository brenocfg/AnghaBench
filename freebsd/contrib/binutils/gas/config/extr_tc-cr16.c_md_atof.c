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
 char* _ (char*) ; 
 char* atof_ieee (char*,int,scalar_t__*) ; 
 char* input_line_pointer ; 
 int /*<<< orphan*/  md_number_to_chars (char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  target_big_endian ; 

char *
md_atof (int type, char *litP, int *sizeP)
{
  int prec;
  int i;
  LITTLENUM_TYPE words[4];
  char *t;

  switch (type)
    {
      case 'f':
        prec = 2;
        break;

      case 'd':
        prec = 4;
        break;

      default:
        *sizeP = 0;
        return _("bad call to md_atof");
    }

  t = atof_ieee (input_line_pointer, type, words);
  if (t)
    input_line_pointer = t;

  *sizeP = prec * 2;

  if (! target_big_endian)
    {
      for (i = prec - 1; i >= 0; i--)
        {
          md_number_to_chars (litP, (valueT) words[i], 2);
          litP += 2;
        }
    }
  else
    {
      for (i = 0; i < prec; i++)
        {
          md_number_to_chars (litP, (valueT) words[i], 2);
          litP += 2;
        }
    }

  return NULL;
}