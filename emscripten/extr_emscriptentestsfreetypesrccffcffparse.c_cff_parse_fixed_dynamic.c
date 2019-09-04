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
typedef  int FT_Long ;
typedef  int FT_Int ;
typedef  int FT_Fixed ;
typedef  int FT_Byte ;

/* Variables and functions */
 int /*<<< orphan*/  FT_ASSERT (int*) ; 
 int FT_DivFix (int,int) ; 
 int cff_parse_integer (int*,int*) ; 
 int cff_parse_real (int*,int*,int /*<<< orphan*/ ,int*) ; 
 int* power_tens ; 

__attribute__((used)) static FT_Fixed
  cff_parse_fixed_dynamic( FT_Byte**  d,
                           FT_Long*   scaling )
  {
    FT_ASSERT( scaling );

    if ( **d == 30 )
      return cff_parse_real( d[0], d[1], 0, scaling );
    else
    {
      FT_Long  number;
      FT_Int   integer_length;


      number = cff_parse_integer( d[0], d[1] );

      if ( number > 0x7FFFL )
      {
        for ( integer_length = 5; integer_length < 10; integer_length++ )
          if ( number < power_tens[integer_length] )
            break;

        if ( ( number / power_tens[integer_length - 5] ) > 0x7FFFL )
        {
          *scaling = integer_length - 4;
          return FT_DivFix( number, power_tens[integer_length - 4] );
        }
        else
        {
          *scaling = integer_length - 5;
          return FT_DivFix( number, power_tens[integer_length - 5] );
        }
      }
      else
      {
        *scaling = 0;
        return number << 16;
      }
    }
  }