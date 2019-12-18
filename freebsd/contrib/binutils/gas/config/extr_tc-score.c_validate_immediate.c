#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int* range; } ;

/* Variables and functions */
 scalar_t__ FAIL ; 
 unsigned int _IMM16_NEG ; 
#define  _SIMM14 132 
 unsigned int _SIMM14_NEG ; 
#define  _SIMM16_NEG 131 
#define  _VALUE 130 
#define  _VALUE_HI16 129 
#define  _VALUE_LO16 128 
 TYPE_1__* score_df_range ; 

__attribute__((used)) static int
validate_immediate (int val, unsigned int data_type, int hex_p)
{
  switch (data_type)
    {
    case _VALUE_HI16:
      {
        int val_hi = ((val & 0xffff0000) >> 16);

        if (score_df_range[data_type].range[0] <= val_hi
            && val_hi <= score_df_range[data_type].range[1])
	  return val_hi;
      }
      break;

    case _VALUE_LO16:
      {
        int val_lo = (val & 0xffff);

        if (score_df_range[data_type].range[0] <= val_lo
            && val_lo <= score_df_range[data_type].range[1])
	  return val_lo;
      }
      break;

    case _VALUE:
      return val;
      break;

    case _SIMM14:
      if (hex_p == 1)
        {
          if (!(val >= -0x2000 && val <= 0x3fff))
            {
              return (int) FAIL;
            }
        }
      else
        {
          if (!(val >= -8192 && val <= 8191))
            {
              return (int) FAIL;
            }
        }

      return val;
      break;

    case _SIMM16_NEG:
      if (hex_p == 1)
        {
          if (!(val >= -0x7fff && val <= 0xffff && val != 0x8000))
            {
              return (int) FAIL;
            }
        }
      else
        {
          if (!(val >= -32767 && val <= 32768))
            {
              return (int) FAIL;
            }
        }

      val = -val;
      return val;
      break;

    default:
      if (data_type == _SIMM14_NEG || data_type == _IMM16_NEG)
	val = -val;

      if (score_df_range[data_type].range[0] <= val
          && val <= score_df_range[data_type].range[1])
	return val;

      break;
    }

  return (int) FAIL;
}