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
typedef  int UInt32 ;
typedef  size_t UInt16 ;
typedef  int UChar ;
struct TYPE_4__ {size_t* mtfv; int verbosity; int nMTF; int nInUse; int** len; int** len_pack; int* selector; int* selectorMtf; int** code; int numZ; scalar_t__* inUse; scalar_t__** rfreq; scalar_t__* mtfFreq; int /*<<< orphan*/  nblock; } ;
typedef  int Int32 ;
typedef  TYPE_1__ EState ;
typedef  scalar_t__ Bool ;

/* Variables and functions */
 int /*<<< orphan*/  AssertH (int,int) ; 
 int /*<<< orphan*/  BZ2_hbAssignCodes (int*,int*,int,int,int) ; 
 int /*<<< orphan*/  BZ2_hbMakeCodeLengths (int*,scalar_t__*,int,int) ; 
 void* BZ_GREATER_ICOST ; 
 int BZ_G_SIZE ; 
 int /*<<< orphan*/  BZ_ITAH (int) ; 
 int /*<<< orphan*/  BZ_ITER (int) ; 
 int /*<<< orphan*/  BZ_ITUR (int) ; 
 int BZ_LESSER_ICOST ; 
 int BZ_MAX_SELECTORS ; 
 int BZ_N_GROUPS ; 
 int BZ_N_ITERS ; 
 scalar_t__ False ; 
 scalar_t__ True ; 
 int /*<<< orphan*/  VPrintf0 (char*) ; 
 int /*<<< orphan*/  VPrintf1 (char*,int) ; 
 int /*<<< orphan*/  VPrintf2 (char*,int,int) ; 
 int /*<<< orphan*/  VPrintf3 (char*,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  VPrintf5 (char*,int,int,int,int,double) ; 
 int /*<<< orphan*/  bsW (TYPE_1__*,int,int) ; 

__attribute__((used)) static
void sendMTFValues ( EState* s )
{
   Int32 v, t, i, j, gs, ge, totc, bt, bc, iter;
   Int32 nSelectors, alphaSize, minLen, maxLen, selCtr;
   Int32 nGroups, nBytes;

   /*--
   UChar  len [BZ_N_GROUPS][BZ_MAX_ALPHA_SIZE];
   is a global since the decoder also needs it.

   Int32  code[BZ_N_GROUPS][BZ_MAX_ALPHA_SIZE];
   Int32  rfreq[BZ_N_GROUPS][BZ_MAX_ALPHA_SIZE];
   are also globals only used in this proc.
   Made global to keep stack frame size small.
   --*/


   UInt16 cost[BZ_N_GROUPS];
   Int32  fave[BZ_N_GROUPS];

   UInt16* mtfv = s->mtfv;

   if (s->verbosity >= 3)
      VPrintf3( "      %d in block, %d after MTF & 1-2 coding, "
                "%d+2 syms in use\n", 
                s->nblock, s->nMTF, s->nInUse );

   alphaSize = s->nInUse+2;
   for (t = 0; t < BZ_N_GROUPS; t++)
      for (v = 0; v < alphaSize; v++)
         s->len[t][v] = BZ_GREATER_ICOST;

   /*--- Decide how many coding tables to use ---*/
   AssertH ( s->nMTF > 0, 3001 );
   if (s->nMTF < 200)  nGroups = 2; else
   if (s->nMTF < 600)  nGroups = 3; else
   if (s->nMTF < 1200) nGroups = 4; else
   if (s->nMTF < 2400) nGroups = 5; else
                       nGroups = 6;

   /*--- Generate an initial set of coding tables ---*/
   { 
      Int32 nPart, remF, tFreq, aFreq;

      nPart = nGroups;
      remF  = s->nMTF;
      gs = 0;
      while (nPart > 0) {
         tFreq = remF / nPart;
         ge = gs-1;
         aFreq = 0;
         while (aFreq < tFreq && ge < alphaSize-1) {
            ge++;
            aFreq += s->mtfFreq[ge];
         }

         if (ge > gs 
             && nPart != nGroups && nPart != 1 
             && ((nGroups-nPart) % 2 == 1)) {
            aFreq -= s->mtfFreq[ge];
            ge--;
         }

         if (s->verbosity >= 3)
            VPrintf5( "      initial group %d, [%d .. %d], "
                      "has %d syms (%4.1f%%)\n",
                      nPart, gs, ge, aFreq, 
                      (100.0 * (float)aFreq) / (float)(s->nMTF) );
 
         for (v = 0; v < alphaSize; v++)
            if (v >= gs && v <= ge) 
               s->len[nPart-1][v] = BZ_LESSER_ICOST; else
               s->len[nPart-1][v] = BZ_GREATER_ICOST;
 
         nPart--;
         gs = ge+1;
         remF -= aFreq;
      }
   }

   /*--- 
      Iterate up to BZ_N_ITERS times to improve the tables.
   ---*/
   for (iter = 0; iter < BZ_N_ITERS; iter++) {

      for (t = 0; t < nGroups; t++) fave[t] = 0;

      for (t = 0; t < nGroups; t++)
         for (v = 0; v < alphaSize; v++)
            s->rfreq[t][v] = 0;

      /*---
        Set up an auxiliary length table which is used to fast-track
	the common case (nGroups == 6). 
      ---*/
      if (nGroups == 6) {
         for (v = 0; v < alphaSize; v++) {
            s->len_pack[v][0] = (s->len[1][v] << 16) | s->len[0][v];
            s->len_pack[v][1] = (s->len[3][v] << 16) | s->len[2][v];
            s->len_pack[v][2] = (s->len[5][v] << 16) | s->len[4][v];
	 }
      }

      nSelectors = 0;
      totc = 0;
      gs = 0;
      while (True) {

         /*--- Set group start & end marks. --*/
         if (gs >= s->nMTF) break;
         ge = gs + BZ_G_SIZE - 1; 
         if (ge >= s->nMTF) ge = s->nMTF-1;

         /*-- 
            Calculate the cost of this group as coded
            by each of the coding tables.
         --*/
         for (t = 0; t < nGroups; t++) cost[t] = 0;

         if (nGroups == 6 && 50 == ge-gs+1) {
            /*--- fast track the common case ---*/
            register UInt32 cost01, cost23, cost45;
            register UInt16 icv;
            cost01 = cost23 = cost45 = 0;

#           define BZ_ITER(nn)                \
               icv = mtfv[gs+(nn)];           \
               cost01 += s->len_pack[icv][0]; \
               cost23 += s->len_pack[icv][1]; \
               cost45 += s->len_pack[icv][2]; \

            BZ_ITER(0);  BZ_ITER(1);  BZ_ITER(2);  BZ_ITER(3);  BZ_ITER(4);
            BZ_ITER(5);  BZ_ITER(6);  BZ_ITER(7);  BZ_ITER(8);  BZ_ITER(9);
            BZ_ITER(10); BZ_ITER(11); BZ_ITER(12); BZ_ITER(13); BZ_ITER(14);
            BZ_ITER(15); BZ_ITER(16); BZ_ITER(17); BZ_ITER(18); BZ_ITER(19);
            BZ_ITER(20); BZ_ITER(21); BZ_ITER(22); BZ_ITER(23); BZ_ITER(24);
            BZ_ITER(25); BZ_ITER(26); BZ_ITER(27); BZ_ITER(28); BZ_ITER(29);
            BZ_ITER(30); BZ_ITER(31); BZ_ITER(32); BZ_ITER(33); BZ_ITER(34);
            BZ_ITER(35); BZ_ITER(36); BZ_ITER(37); BZ_ITER(38); BZ_ITER(39);
            BZ_ITER(40); BZ_ITER(41); BZ_ITER(42); BZ_ITER(43); BZ_ITER(44);
            BZ_ITER(45); BZ_ITER(46); BZ_ITER(47); BZ_ITER(48); BZ_ITER(49);

#           undef BZ_ITER

            cost[0] = cost01 & 0xffff; cost[1] = cost01 >> 16;
            cost[2] = cost23 & 0xffff; cost[3] = cost23 >> 16;
            cost[4] = cost45 & 0xffff; cost[5] = cost45 >> 16;

         } else {
	    /*--- slow version which correctly handles all situations ---*/
            for (i = gs; i <= ge; i++) { 
               UInt16 icv = mtfv[i];
               for (t = 0; t < nGroups; t++) cost[t] += s->len[t][icv];
            }
         }
 
         /*-- 
            Find the coding table which is best for this group,
            and record its identity in the selector table.
         --*/
         bc = 999999999; bt = -1;
         for (t = 0; t < nGroups; t++)
            if (cost[t] < bc) { bc = cost[t]; bt = t; };
         totc += bc;
         fave[bt]++;
         s->selector[nSelectors] = bt;
         nSelectors++;

         /*-- 
            Increment the symbol frequencies for the selected table.
          --*/
         if (nGroups == 6 && 50 == ge-gs+1) {
            /*--- fast track the common case ---*/

#           define BZ_ITUR(nn) s->rfreq[bt][ mtfv[gs+(nn)] ]++

            BZ_ITUR(0);  BZ_ITUR(1);  BZ_ITUR(2);  BZ_ITUR(3);  BZ_ITUR(4);
            BZ_ITUR(5);  BZ_ITUR(6);  BZ_ITUR(7);  BZ_ITUR(8);  BZ_ITUR(9);
            BZ_ITUR(10); BZ_ITUR(11); BZ_ITUR(12); BZ_ITUR(13); BZ_ITUR(14);
            BZ_ITUR(15); BZ_ITUR(16); BZ_ITUR(17); BZ_ITUR(18); BZ_ITUR(19);
            BZ_ITUR(20); BZ_ITUR(21); BZ_ITUR(22); BZ_ITUR(23); BZ_ITUR(24);
            BZ_ITUR(25); BZ_ITUR(26); BZ_ITUR(27); BZ_ITUR(28); BZ_ITUR(29);
            BZ_ITUR(30); BZ_ITUR(31); BZ_ITUR(32); BZ_ITUR(33); BZ_ITUR(34);
            BZ_ITUR(35); BZ_ITUR(36); BZ_ITUR(37); BZ_ITUR(38); BZ_ITUR(39);
            BZ_ITUR(40); BZ_ITUR(41); BZ_ITUR(42); BZ_ITUR(43); BZ_ITUR(44);
            BZ_ITUR(45); BZ_ITUR(46); BZ_ITUR(47); BZ_ITUR(48); BZ_ITUR(49);

#           undef BZ_ITUR

         } else {
	    /*--- slow version which correctly handles all situations ---*/
            for (i = gs; i <= ge; i++)
               s->rfreq[bt][ mtfv[i] ]++;
         }

         gs = ge+1;
      }
      if (s->verbosity >= 3) {
         VPrintf2 ( "      pass %d: size is %d, grp uses are ", 
                   iter+1, totc/8 );
         for (t = 0; t < nGroups; t++)
            VPrintf1 ( "%d ", fave[t] );
         VPrintf0 ( "\n" );
      }

      /*--
        Recompute the tables based on the accumulated frequencies.
      --*/
      /* maxLen was changed from 20 to 17 in bzip2-1.0.3.  See 
         comment in huffman.c for details. */
      for (t = 0; t < nGroups; t++)
         BZ2_hbMakeCodeLengths ( &(s->len[t][0]), &(s->rfreq[t][0]), 
                                 alphaSize, 17 /*20*/ );
   }


   AssertH( nGroups < 8, 3002 );
   AssertH( nSelectors < 32768 &&
            nSelectors <= BZ_MAX_SELECTORS,
            3003 );


   /*--- Compute MTF values for the selectors. ---*/
   {
      UChar pos[BZ_N_GROUPS], ll_i, tmp2, tmp;
      for (i = 0; i < nGroups; i++) pos[i] = i;
      for (i = 0; i < nSelectors; i++) {
         ll_i = s->selector[i];
         j = 0;
         tmp = pos[j];
         while ( ll_i != tmp ) {
            j++;
            tmp2 = tmp;
            tmp = pos[j];
            pos[j] = tmp2;
         };
         pos[0] = tmp;
         s->selectorMtf[i] = j;
      }
   };

   /*--- Assign actual codes for the tables. --*/
   for (t = 0; t < nGroups; t++) {
      minLen = 32;
      maxLen = 0;
      for (i = 0; i < alphaSize; i++) {
         if (s->len[t][i] > maxLen) maxLen = s->len[t][i];
         if (s->len[t][i] < minLen) minLen = s->len[t][i];
      }
      AssertH ( !(maxLen > 17 /*20*/ ), 3004 );
      AssertH ( !(minLen < 1),  3005 );
      BZ2_hbAssignCodes ( &(s->code[t][0]), &(s->len[t][0]), 
                          minLen, maxLen, alphaSize );
   }

   /*--- Transmit the mapping table. ---*/
   { 
      Bool inUse16[16];
      for (i = 0; i < 16; i++) {
          inUse16[i] = False;
          for (j = 0; j < 16; j++)
             if (s->inUse[i * 16 + j]) inUse16[i] = True;
      }
     
      nBytes = s->numZ;
      for (i = 0; i < 16; i++)
         if (inUse16[i]) bsW(s,1,1); else bsW(s,1,0);

      for (i = 0; i < 16; i++)
         if (inUse16[i])
            for (j = 0; j < 16; j++) {
               if (s->inUse[i * 16 + j]) bsW(s,1,1); else bsW(s,1,0);
            }

      if (s->verbosity >= 3) 
         VPrintf1( "      bytes: mapping %d, ", s->numZ-nBytes );
   }

   /*--- Now the selectors. ---*/
   nBytes = s->numZ;
   bsW ( s, 3, nGroups );
   bsW ( s, 15, nSelectors );
   for (i = 0; i < nSelectors; i++) { 
      for (j = 0; j < s->selectorMtf[i]; j++) bsW(s,1,1);
      bsW(s,1,0);
   }
   if (s->verbosity >= 3)
      VPrintf1( "selectors %d, ", s->numZ-nBytes );

   /*--- Now the coding tables. ---*/
   nBytes = s->numZ;

   for (t = 0; t < nGroups; t++) {
      Int32 curr = s->len[t][0];
      bsW ( s, 5, curr );
      for (i = 0; i < alphaSize; i++) {
         while (curr < s->len[t][i]) { bsW(s,2,2); curr++; /* 10 */ };
         while (curr > s->len[t][i]) { bsW(s,2,3); curr--; /* 11 */ };
         bsW ( s, 1, 0 );
      }
   }

   if (s->verbosity >= 3)
      VPrintf1 ( "code lengths %d, ", s->numZ-nBytes );

   /*--- And finally, the block data proper ---*/
   nBytes = s->numZ;
   selCtr = 0;
   gs = 0;
   while (True) {
      if (gs >= s->nMTF) break;
      ge = gs + BZ_G_SIZE - 1; 
      if (ge >= s->nMTF) ge = s->nMTF-1;
      AssertH ( s->selector[selCtr] < nGroups, 3006 );

      if (nGroups == 6 && 50 == ge-gs+1) {
            /*--- fast track the common case ---*/
            UInt16 mtfv_i;
            UChar* s_len_sel_selCtr 
               = &(s->len[s->selector[selCtr]][0]);
            Int32* s_code_sel_selCtr
               = &(s->code[s->selector[selCtr]][0]);

#           define BZ_ITAH(nn)                      \
               mtfv_i = mtfv[gs+(nn)];              \
               bsW ( s,                             \
                     s_len_sel_selCtr[mtfv_i],      \
                     s_code_sel_selCtr[mtfv_i] )

            BZ_ITAH(0);  BZ_ITAH(1);  BZ_ITAH(2);  BZ_ITAH(3);  BZ_ITAH(4);
            BZ_ITAH(5);  BZ_ITAH(6);  BZ_ITAH(7);  BZ_ITAH(8);  BZ_ITAH(9);
            BZ_ITAH(10); BZ_ITAH(11); BZ_ITAH(12); BZ_ITAH(13); BZ_ITAH(14);
            BZ_ITAH(15); BZ_ITAH(16); BZ_ITAH(17); BZ_ITAH(18); BZ_ITAH(19);
            BZ_ITAH(20); BZ_ITAH(21); BZ_ITAH(22); BZ_ITAH(23); BZ_ITAH(24);
            BZ_ITAH(25); BZ_ITAH(26); BZ_ITAH(27); BZ_ITAH(28); BZ_ITAH(29);
            BZ_ITAH(30); BZ_ITAH(31); BZ_ITAH(32); BZ_ITAH(33); BZ_ITAH(34);
            BZ_ITAH(35); BZ_ITAH(36); BZ_ITAH(37); BZ_ITAH(38); BZ_ITAH(39);
            BZ_ITAH(40); BZ_ITAH(41); BZ_ITAH(42); BZ_ITAH(43); BZ_ITAH(44);
            BZ_ITAH(45); BZ_ITAH(46); BZ_ITAH(47); BZ_ITAH(48); BZ_ITAH(49);

#           undef BZ_ITAH

      } else {
	 /*--- slow version which correctly handles all situations ---*/
         for (i = gs; i <= ge; i++) {
            bsW ( s, 
                  s->len  [s->selector[selCtr]] [mtfv[i]],
                  s->code [s->selector[selCtr]] [mtfv[i]] );
         }
      }


      gs = ge+1;
      selCtr++;
   }
   AssertH( selCtr == nSelectors, 3007 );

   if (s->verbosity >= 3)
      VPrintf1( "codes %d\n", s->numZ-nBytes );
}