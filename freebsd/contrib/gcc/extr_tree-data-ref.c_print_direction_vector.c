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
typedef  int* lambda_vector ;
typedef  enum data_dependence_direction { ____Placeholder_data_dependence_direction } data_dependence_direction ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
#define  dir_equal 134 
#define  dir_negative 133 
#define  dir_negative_or_equal 132 
#define  dir_positive 131 
#define  dir_positive_or_equal 130 
#define  dir_positive_or_negative 129 
#define  dir_star 128 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ *,char*) ; 

void
print_direction_vector (FILE *outf,
			lambda_vector dirv,
			int length)
{
  int eq;

  for (eq = 0; eq < length; eq++)
    {
      enum data_dependence_direction dir = dirv[eq];

      switch (dir)
	{
	case dir_positive:
	  fprintf (outf, "    +");
	  break;
	case dir_negative:
	  fprintf (outf, "    -");
	  break;
	case dir_equal:
	  fprintf (outf, "    =");
	  break;
	case dir_positive_or_equal:
	  fprintf (outf, "   +=");
	  break;
	case dir_positive_or_negative:
	  fprintf (outf, "   +-");
	  break;
	case dir_negative_or_equal:
	  fprintf (outf, "   -=");
	  break;
	case dir_star:
	  fprintf (outf, "    *");
	  break;
	default:
	  fprintf (outf, "indep");
	  break;
	}
    }
  fprintf (outf, "\n");
}