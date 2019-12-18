#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
typedef  int UChar ;
struct TYPE_11__ {size_t nblock; int blockCRC; int combinedCRC; int blockNo; int verbosity; int* zbits; int /*<<< orphan*/  origPtr; scalar_t__ blockSize100k; scalar_t__ arr2; scalar_t__ numZ; } ;
typedef  TYPE_1__ EState ;
typedef  scalar_t__ Bool ;

/* Variables and functions */
 int /*<<< orphan*/  BZ2_blockSort (TYPE_1__*) ; 
 int /*<<< orphan*/  BZ2_bsInitWrite (TYPE_1__*) ; 
 int /*<<< orphan*/  BZ_FINALISE_CRC (int) ; 
 scalar_t__ BZ_HDR_0 ; 
 int BZ_HDR_B ; 
 int BZ_HDR_Z ; 
 int BZ_HDR_h ; 
 int /*<<< orphan*/  VPrintf1 (char*,int) ; 
 int /*<<< orphan*/  VPrintf4 (char*,int,int,int,size_t) ; 
 int /*<<< orphan*/  bsFinishWrite (TYPE_1__*) ; 
 int /*<<< orphan*/  bsPutUChar (TYPE_1__*,int) ; 
 int /*<<< orphan*/  bsPutUInt32 (TYPE_1__*,int) ; 
 int /*<<< orphan*/  bsW (TYPE_1__*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  generateMTFValues (TYPE_1__*) ; 
 int /*<<< orphan*/  sendMTFValues (TYPE_1__*) ; 

void BZ2_compressBlock ( EState* s, Bool is_last_block )
{
   if (s->nblock > 0) {

      BZ_FINALISE_CRC ( s->blockCRC );
      s->combinedCRC = (s->combinedCRC << 1) | (s->combinedCRC >> 31);
      s->combinedCRC ^= s->blockCRC;
      if (s->blockNo > 1) s->numZ = 0;

      if (s->verbosity >= 2)
         VPrintf4( "    block %d: crc = 0x%08x, "
                   "combined CRC = 0x%08x, size = %d\n",
                   s->blockNo, s->blockCRC, s->combinedCRC, s->nblock );

      BZ2_blockSort ( s );
   }

   s->zbits = (UChar*) (&((UChar*)s->arr2)[s->nblock]);

   /*-- If this is the first block, create the stream header. --*/
   if (s->blockNo == 1) {
      BZ2_bsInitWrite ( s );
      bsPutUChar ( s, BZ_HDR_B );
      bsPutUChar ( s, BZ_HDR_Z );
      bsPutUChar ( s, BZ_HDR_h );
      bsPutUChar ( s, (UChar)(BZ_HDR_0 + s->blockSize100k) );
   }

   if (s->nblock > 0) {

      bsPutUChar ( s, 0x31 ); bsPutUChar ( s, 0x41 );
      bsPutUChar ( s, 0x59 ); bsPutUChar ( s, 0x26 );
      bsPutUChar ( s, 0x53 ); bsPutUChar ( s, 0x59 );

      /*-- Now the block's CRC, so it is in a known place. --*/
      bsPutUInt32 ( s, s->blockCRC );

      /*-- 
         Now a single bit indicating (non-)randomisation. 
         As of version 0.9.5, we use a better sorting algorithm
         which makes randomisation unnecessary.  So always set
         the randomised bit to 'no'.  Of course, the decoder
         still needs to be able to handle randomised blocks
         so as to maintain backwards compatibility with
         older versions of bzip2.
      --*/
      bsW(s,1,0);

      bsW ( s, 24, s->origPtr );
      generateMTFValues ( s );
      sendMTFValues ( s );
   }


   /*-- If this is the last block, add the stream trailer. --*/
   if (is_last_block) {

      bsPutUChar ( s, 0x17 ); bsPutUChar ( s, 0x72 );
      bsPutUChar ( s, 0x45 ); bsPutUChar ( s, 0x38 );
      bsPutUChar ( s, 0x50 ); bsPutUChar ( s, 0x90 );
      bsPutUInt32 ( s, s->combinedCRC );
      if (s->verbosity >= 2)
         VPrintf1( "    final combined CRC = 0x%08x\n   ", s->combinedCRC );
      bsFinishWrite ( s );
   }
}