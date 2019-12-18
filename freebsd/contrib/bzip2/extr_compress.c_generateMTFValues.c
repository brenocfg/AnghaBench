#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  size_t UInt32 ;
typedef  size_t UInt16 ;
typedef  size_t UChar ;
struct TYPE_4__ {size_t* ptr; size_t* block; size_t* mtfv; int nInUse; size_t nblock; size_t* unseqToSeq; size_t nMTF; scalar_t__* mtfFreq; } ;
typedef  size_t Int32 ;
typedef  TYPE_1__ EState ;

/* Variables and functions */
 int /*<<< orphan*/  AssertD (int,char*) ; 
 size_t BZ_RUNA ; 
 size_t BZ_RUNB ; 
 scalar_t__ True ; 
 int /*<<< orphan*/  makeMaps_e (TYPE_1__*) ; 

__attribute__((used)) static
void generateMTFValues ( EState* s )
{
   UChar   yy[256];
   Int32   i, j;
   Int32   zPend;
   Int32   wr;
   Int32   EOB;

   /* 
      After sorting (eg, here),
         s->arr1 [ 0 .. s->nblock-1 ] holds sorted order,
         and
         ((UChar*)s->arr2) [ 0 .. s->nblock-1 ] 
         holds the original block data.

      The first thing to do is generate the MTF values,
      and put them in
         ((UInt16*)s->arr1) [ 0 .. s->nblock-1 ].
      Because there are strictly fewer or equal MTF values
      than block values, ptr values in this area are overwritten
      with MTF values only when they are no longer needed.

      The final compressed bitstream is generated into the
      area starting at
         (UChar*) (&((UChar*)s->arr2)[s->nblock])

      These storage aliases are set up in bzCompressInit(),
      except for the last one, which is arranged in 
      compressBlock().
   */
   UInt32* ptr   = s->ptr;
   UChar* block  = s->block;
   UInt16* mtfv  = s->mtfv;

   makeMaps_e ( s );
   EOB = s->nInUse+1;

   for (i = 0; i <= EOB; i++) s->mtfFreq[i] = 0;

   wr = 0;
   zPend = 0;
   for (i = 0; i < s->nInUse; i++) yy[i] = (UChar) i;

   for (i = 0; i < s->nblock; i++) {
      UChar ll_i;
      AssertD ( wr <= i, "generateMTFValues(1)" );
      j = ptr[i]-1; if (j < 0) j += s->nblock;
      ll_i = s->unseqToSeq[block[j]];
      AssertD ( ll_i < s->nInUse, "generateMTFValues(2a)" );

      if (yy[0] == ll_i) { 
         zPend++;
      } else {

         if (zPend > 0) {
            zPend--;
            while (True) {
               if (zPend & 1) {
                  mtfv[wr] = BZ_RUNB; wr++; 
                  s->mtfFreq[BZ_RUNB]++; 
               } else {
                  mtfv[wr] = BZ_RUNA; wr++; 
                  s->mtfFreq[BZ_RUNA]++; 
               }
               if (zPend < 2) break;
               zPend = (zPend - 2) / 2;
            };
            zPend = 0;
         }
         {
            register UChar  rtmp;
            register UChar* ryy_j;
            register UChar  rll_i;
            rtmp  = yy[1];
            yy[1] = yy[0];
            ryy_j = &(yy[1]);
            rll_i = ll_i;
            while ( rll_i != rtmp ) {
               register UChar rtmp2;
               ryy_j++;
               rtmp2  = rtmp;
               rtmp   = *ryy_j;
               *ryy_j = rtmp2;
            };
            yy[0] = rtmp;
            j = ryy_j - &(yy[0]);
            mtfv[wr] = j+1; wr++; s->mtfFreq[j+1]++;
         }

      }
   }

   if (zPend > 0) {
      zPend--;
      while (True) {
         if (zPend & 1) {
            mtfv[wr] = BZ_RUNB; wr++; 
            s->mtfFreq[BZ_RUNB]++; 
         } else {
            mtfv[wr] = BZ_RUNA; wr++; 
            s->mtfFreq[BZ_RUNA]++; 
         }
         if (zPend < 2) break;
         zPend = (zPend - 2) / 2;
      };
      zPend = 0;
   }

   mtfv[wr] = EOB; wr++; s->mtfFreq[EOB]++;

   s->nMTF = wr;
}