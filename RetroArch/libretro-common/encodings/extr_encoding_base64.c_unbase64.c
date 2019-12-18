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
 scalar_t__ malloc (int) ; 
 int* unb64 ; 

unsigned char* unbase64(const char* ascii, int len, int *flen)
{
   const unsigned char *safeAsciiPtr = (const unsigned char*) ascii;
   unsigned char *bin;
   int cb                            = 0;
   int charNo;
   int pad                           = 0;

   if (len < 2) { /* 2 accesses below would be OOB. */
      /* catch empty string, return NULL as result. */

      /* ERROR: You passed an invalid base64 string (too short). 
       * You get NULL back. */
      *flen = 0;
      return 0;
   }

   if(safeAsciiPtr[len-1]=='=')
      ++pad;
   if(safeAsciiPtr[len-2]=='=')
      ++pad;
  
   *flen = 3*len/4 - pad;
   bin = (unsigned char*)malloc(*flen);

   if (!bin)
   {
      /* ERROR: unbase64 could not allocate enough memory. */
      return 0;
   }
  
   for (charNo=0; charNo <= len-4-pad; charNo+=4)
   {
      int A = unb64[safeAsciiPtr[charNo]];
      int B = unb64[safeAsciiPtr[charNo+1]];
      int C = unb64[safeAsciiPtr[charNo+2]];
      int D = unb64[safeAsciiPtr[charNo+3]];
    
      bin[cb++] = (A<<2) | (B>>4);
      bin[cb++] = (B<<4) | (C>>2);
      bin[cb++] = (C<<6) | (D);
   }
  
   if (pad==1)
   {
      int A = unb64[safeAsciiPtr[charNo]];
      int B = unb64[safeAsciiPtr[charNo+1]];
      int C = unb64[safeAsciiPtr[charNo+2]];
    
      bin[cb++] = (A<<2) | (B>>4);
      bin[cb++] = (B<<4) | (C>>2);
   }
   else if (pad==2)
   {
      int A = unb64[safeAsciiPtr[charNo]];
      int B = unb64[safeAsciiPtr[charNo+1]];
    
      bin[cb++] = (A<<2) | (B>>4);
   }
  
   return bin;
}