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
typedef  int rc_uint_type ;
typedef  char bfd_byte ;

/* Variables and functions */
 int /*<<< orphan*/  ISPRINT (char const) ; 

__attribute__((used)) static int
test_rc_datablock_text (rc_uint_type length, const bfd_byte *data)
{
  int has_nl;
  rc_uint_type c;
  rc_uint_type i;
  
  if (length <= 1)
    return 0;

  has_nl = 0;
  for (i = 0, c = 0; i < length; i++)
    {
      if (! ISPRINT (data[i]) && data[i] != '\n'
      	  && ! (data[i] == '\r' && (i + 1) < length && data[i + 1] == '\n')
      	  && data[i] != '\t'
	  && ! (data[i] == 0 && (i + 1) != length))
	{
	  if (data[i] <= 7)
	    return 0;
	  c++;
	}
      else if (data[i] == '\n') has_nl++;
    }
  if (length > 80 && ! has_nl)
    return 0;
  c = (((c * 10000) + (i / 100) - 1)) / i;
  if (c >= 150)
    return 0;
  return 1;
}