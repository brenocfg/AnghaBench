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
 char* b64 ; 
 scalar_t__ malloc (int) ; 

char* base64(const void* binaryData, int len, int *flen)
{
   const unsigned char* bin          = (const unsigned char*) binaryData;
   char* res;
  
   int rc = 0; /* result counter */
   int byteNo; /* I need this after the loop */
  
   int modulusLen = len % 3 ;

   /* 2 gives 1 and 1 gives 2, but 0 gives 0. */
   int pad = ((modulusLen&1)<<1) + ((modulusLen&2)>>1);

   *flen = 4*(len + pad)/3;
   res = (char*) malloc(*flen + 1); /* and one for the null */
   if (!res)
   {
      /* ERROR: base64 could not allocate enough memory. */
      return 0;
   }
  
   for (byteNo=0; byteNo <= len-3; byteNo+=3)
   {
      unsigned char BYTE0            = bin[byteNo];
      unsigned char BYTE1            = bin[byteNo+1];
      unsigned char BYTE2            = bin[byteNo+2];

      res[rc++] = b64[BYTE0 >> 2];
      res[rc++] = b64[((0x3&BYTE0)<<4) + (BYTE1 >> 4)];
      res[rc++] = b64[((0x0f&BYTE1)<<2) + (BYTE2>>6)];
      res[rc++] = b64[0x3f&BYTE2];
   }
  
   if (pad==2)
   {
      res[rc++] = b64[bin[byteNo] >> 2];
      res[rc++] = b64[(0x3&bin[byteNo])<<4];
      res[rc++] = '=';
      res[rc++] = '=';
   }
   else if (pad==1)
   {
      res[rc++] = b64[bin[byteNo] >> 2];
      res[rc++] = b64[((0x3&bin[byteNo])<<4) + (bin[byteNo+1] >> 4)];
      res[rc++] = b64[(0x0f&bin[byteNo+1])<<2];
      res[rc++] = '=';
   }
  
   res[rc]=0; /* NULL TERMINATOR! ;) */
   return res;
}