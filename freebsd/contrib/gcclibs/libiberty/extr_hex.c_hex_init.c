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

/* Variables and functions */
 int _hex_array_size ; 
 int _hex_bad ; 
 int* _hex_value ; 

void
hex_init (void)
{
#ifndef HEX_TABLE_INITIALIZED
  int i;

  for (i=0; i<_hex_array_size; i++)
    {
      switch (i)
	{
	case '0': _hex_value[i] = 0; break;
	case '1': _hex_value[i] = 1; break;
	case '2': _hex_value[i] = 2; break;
	case '3': _hex_value[i] = 3; break;
	case '4': _hex_value[i] = 4; break;
	case '5': _hex_value[i] = 5; break;
	case '6': _hex_value[i] = 6; break;
	case '7': _hex_value[i] = 7; break;
	case '8': _hex_value[i] = 8; break;
	case '9': _hex_value[i] = 9; break;

	case 'a': case 'A': _hex_value[i] = 10; break;
	case 'b': case 'B': _hex_value[i] = 11; break;
	case 'c': case 'C': _hex_value[i] = 12; break;
	case 'd': case 'D': _hex_value[i] = 13; break;
	case 'e': case 'E': _hex_value[i] = 14; break;
	case 'f': case 'F': _hex_value[i] = 15; break;

	default:
	  _hex_value[i] = _hex_bad;
	  break;
	}
    }
#endif
}