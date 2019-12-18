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
typedef  char stbtt_uint8 ;
typedef  int stbtt_uint32 ;
typedef  int stbtt_int32 ;

/* Variables and functions */
 scalar_t__ stbtt_CompareUTF8toUTF16_bigendian (char*,int,char*,int) ; 
 int stbtt__CompareUTF8toUTF16_bigendian_prefix (char*,int,char*,int) ; 
 int ttUSHORT (char*) ; 

__attribute__((used)) static int stbtt__matchpair(stbtt_uint8 *fc, stbtt_uint32 nm, stbtt_uint8 *name,
      stbtt_int32 nlen, stbtt_int32 target_id, stbtt_int32 next_id)
{
   stbtt_int32 i;
   stbtt_int32 count = ttUSHORT(fc+nm+2);
   stbtt_int32 stringOffset = nm + ttUSHORT(fc+nm+4);

   for (i=0; i < count; ++i)
   {
      stbtt_uint32 loc = nm + 6 + 12 * i;
      stbtt_int32 id = ttUSHORT(fc+loc+6);
      if (id == target_id)
      {
         /* find the encoding */
         stbtt_int32 platform = ttUSHORT(fc+loc+0), encoding = ttUSHORT(fc+loc+2), language = ttUSHORT(fc+loc+4);

         /* is this a Unicode encoding? */
         if (platform == 0 || (platform == 3 && encoding == 1) || (platform == 3 && encoding == 10))
         {
            stbtt_int32 slen = ttUSHORT(fc+loc+8);
            stbtt_int32 off = ttUSHORT(fc+loc+10);

            /* check if there's a prefix match */
            stbtt_int32 matchlen = stbtt__CompareUTF8toUTF16_bigendian_prefix(name, nlen, fc+stringOffset+off,slen);
            if (matchlen >= 0)
            {
               /* check for target_id+1 immediately following, with same encoding & language */
               if (i+1 < count && ttUSHORT(fc+loc+12+6) == next_id
                     && ttUSHORT(fc+loc+12) == platform && ttUSHORT(fc+loc+12+2) == encoding
                     && ttUSHORT(fc+loc+12+4) == language)
               {
                  slen = ttUSHORT(fc+loc+12+8);
                  off = ttUSHORT(fc+loc+12+10);

                  if (slen == 0)
                  {
                     if (matchlen == nlen)
                        return 1;
                  }
                  else if (matchlen < nlen && name[matchlen] == ' ')
                  {
                     ++matchlen;
                     if (stbtt_CompareUTF8toUTF16_bigendian((char*)(name+matchlen),
                              nlen-matchlen, (char*)(fc+stringOffset+off),slen))
                        return 1;
                  }
               }
               else
               {
                  /* if nothing immediately following */
                  if (matchlen == nlen)
                     return 1;
               }
            }
         }

         /* @TODO handle other encodings */
      }
   }
   return 0;
}