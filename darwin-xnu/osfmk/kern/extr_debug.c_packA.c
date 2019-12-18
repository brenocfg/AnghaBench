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
typedef  int uint32_t ;
struct TYPE_2__ {char a; char b; char c; char d; char e; char f; char g; char h; } ;
typedef  TYPE_1__ pasc_t ;

/* Variables and functions */
 int MIN (int,int) ; 
 int /*<<< orphan*/  bcopy (char*,char*,int) ; 

int
packA(char *inbuf, uint32_t length, uint32_t buflen)
{
  unsigned int i, j = 0;
  pasc_t pack;
  
  length = MIN(((length + 7) & ~7), buflen);

  for (i = 0; i < length; i+=8)
    {
      pack.a = inbuf[i];
      pack.b = inbuf[i+1];
      pack.c = inbuf[i+2];
      pack.d = inbuf[i+3];
      pack.e = inbuf[i+4];
      pack.f = inbuf[i+5];
      pack.g = inbuf[i+6];
      pack.h = inbuf[i+7];
      bcopy ((char *) &pack, inbuf + j, 7);
      j += 7;
    }
  return j;
}