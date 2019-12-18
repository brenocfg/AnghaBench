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
typedef  unsigned int ULONG ;
typedef  unsigned char UCHAR ;

/* Variables and functions */

ULONG  HashBytesPolynomial(UCHAR *value, unsigned int len)
{
   unsigned char *word = value;
   unsigned int ret = 0;
   unsigned int i;

   for(i=0; i < len; i++)
   {
	  int mod = i % 32;
	  ret ^=(unsigned int) (word[i]) << mod;
	  ret ^=(unsigned int) (word[i]) >> (32 - mod);
   }
   return ret;
}