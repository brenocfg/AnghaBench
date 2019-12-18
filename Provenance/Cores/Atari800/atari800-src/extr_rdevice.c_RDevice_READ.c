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
 int /*<<< orphan*/  CPU_ClrN ; 
 int CPU_regA ; 
 int CPU_regY ; 
 int bufend ; 
 int* bufout ; 
 scalar_t__ linefeeds ; 
 scalar_t__ translation ; 

void RDevice_READ(void)
{
  int j;

  /*bufend = Peek(747);*/
  /*printf("Bufend = %d.\n", bufend);*/

/*  if(bufend >= 0) */
/*  { */
    if(translation)
    {
      if(bufout[0] == 0x0d)
      {
        CPU_regA = 0x9b;
      }
    }
    else
    {
      CPU_regA = bufout[0];
    }

    bufend--;

    for(j = 0; j <= bufend; j++)
    {
      bufout[j] = bufout[j+1];
    }

    /*Cycle the buffer again to skip over linefeed....*/
    if(translation && linefeeds && (bufout[0] == 0x0a))
    {
      for(j = 0; j <= bufend; j++)
      {
        bufout[j] = bufout[j+1];
      }
    }
    /*return; ???*/
/*  } */

  CPU_regY = 1;
  CPU_ClrN;
}