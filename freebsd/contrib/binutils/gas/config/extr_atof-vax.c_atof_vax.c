#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {char sign; int /*<<< orphan*/ * low; int /*<<< orphan*/ * high; scalar_t__ exponent; int /*<<< orphan*/ * leader; } ;
typedef  int /*<<< orphan*/  LITTLENUM_TYPE ;
typedef  TYPE_1__ FLONUM_TYPE ;

/* Variables and functions */
 int GUARD ; 
 int MAX_PRECISION ; 
 scalar_t__ atof_generic (char**,char*,char*,TYPE_1__*) ; 
 scalar_t__ flonum_gen2vax (int,TYPE_1__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  make_invalid_floating_point_number (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,char,int) ; 
 scalar_t__ what_kind_of_float (int,int*,long*) ; 

__attribute__((used)) static char *
atof_vax (char *str,			/* Text to convert to binary.  */
	  int what_kind,		/* 'd', 'f', 'g', 'h'  */
	  LITTLENUM_TYPE *words)	/* Build the binary here.  */
{
  FLONUM_TYPE f;
  LITTLENUM_TYPE bits[MAX_PRECISION + MAX_PRECISION + GUARD];
  /* Extra bits for zeroed low-order bits.
     The 1st MAX_PRECISION are zeroed,
     the last contain flonum bits.  */
  char *return_value;
  int precision;		/* Number of 16-bit words in the format.  */
  long exponent_bits;

  return_value = str;
  f.low = bits + MAX_PRECISION;
  f.high = NULL;
  f.leader = NULL;
  f.exponent = 0;
  f.sign = '\0';

  if (what_kind_of_float (what_kind, &precision, &exponent_bits))
    {
      return_value = NULL;
      make_invalid_floating_point_number (words);
    }

  if (return_value)
    {
      memset (bits, '\0', sizeof (LITTLENUM_TYPE) * MAX_PRECISION);

      /* Use more LittleNums than seems
         necessary: the highest flonum may have
         15 leading 0 bits, so could be useless.  */
      f.high = f.low + precision - 1 + GUARD;

      if (atof_generic (&return_value, ".", "eE", &f))
	{
	  make_invalid_floating_point_number (words);
	  return_value = NULL;
	}
      else if (flonum_gen2vax (what_kind, &f, words))
	return_value = NULL;
    }

  return return_value;
}