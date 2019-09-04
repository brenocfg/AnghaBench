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
 int QR_INT_BITS ; 
 int QR_INT_LOGBITS ; 
 int QR_MINI (int,int) ; 

__attribute__((used)) static void qr_samples_unpack(unsigned char **_blocks,int _nblocks,
 int _nshort_data,int _nshort_blocks,const unsigned *_data_bits,
 const unsigned *_fp_mask,int _dim){
  unsigned bits;
  int      biti;
  int      stride;
  int      blocki;
  int      blockj;
  int      i;
  int      j;
  stride=_dim+QR_INT_BITS-1>>QR_INT_LOGBITS;
  /*If _all_ the blocks are short, don't skip anything (see below).*/
  if(_nshort_blocks>=_nblocks)_nshort_blocks=0;
  /*Scan columns in pairs from right to left.*/
  bits=0;
  for(blocki=blockj=biti=0,j=_dim-1;j>0;j-=2){
    unsigned data1;
    unsigned data2;
    unsigned fp_mask1;
    unsigned fp_mask2;
    int      nbits;
    int      l;
    /*Scan up a pair of columns.*/
    nbits=(_dim-1&QR_INT_BITS-1)+1;
    l=j*stride;
    for(i=stride;i-->0;){
      data1=_data_bits[l+i];
      fp_mask1=_fp_mask[l+i];
      data2=_data_bits[l+i-stride];
      fp_mask2=_fp_mask[l+i-stride];
      while(nbits-->0){
        /*Pull a bit from the right column.*/
        if(!(fp_mask1>>nbits&1)){
          bits=bits<<1|data1>>nbits&1;
          biti++;
        }
        /*Pull a bit from the left column.*/
        if(!(fp_mask2>>nbits&1)){
          bits=bits<<1|data2>>nbits&1;
          biti++;
        }
        /*If we finished a byte, drop it in a block.*/
        if(biti>=8){
          biti-=8;
          *_blocks[blocki++]++=(unsigned char)(bits>>biti);
          /*For whatever reason, the long blocks are at the _end_ of the list,
             instead of the beginning.
            Even worse, the extra bytes they get come at the end of the data
             bytes, before the parity bytes.
            Hence the logic here: when we've filled up the data portion of the
             short blocks, skip directly to the long blocks for the next byte.
            It's also the reason we increment _blocks[blocki] on each store,
             instead of just indexing with blockj (after this iteration the
             number of bytes in each block differs).*/
          if(blocki>=_nblocks)blocki=++blockj==_nshort_data?_nshort_blocks:0;
        }
      }
      nbits=QR_INT_BITS;
    }
    j-=2;
    /*Skip the column with the vertical timing pattern.*/
    if(j==6)j--;
    /*Scan down a pair of columns.*/
    l=j*stride;
    for(i=0;i<stride;i++){
      data1=_data_bits[l+i];
      fp_mask1=_fp_mask[l+i];
      data2=_data_bits[l+i-stride];
      fp_mask2=_fp_mask[l+i-stride];
      nbits=QR_MINI(_dim-(i<<QR_INT_LOGBITS),QR_INT_BITS);
      while(nbits-->0){
        /*Pull a bit from the right column.*/
        if(!(fp_mask1&1)){
          bits=bits<<1|data1&1;
          biti++;
        }
        data1>>=1;
        fp_mask1>>=1;
        /*Pull a bit from the left column.*/
        if(!(fp_mask2&1)){
          bits=bits<<1|data2&1;
          biti++;
        }
        data2>>=1;
        fp_mask2>>=1;
        /*If we finished a byte, drop it in a block.*/
        if(biti>=8){
          biti-=8;
          *_blocks[blocki++]++=(unsigned char)(bits>>biti);
          /*See comments on the "up" loop for the reason behind this mess.*/
          if(blocki>=_nblocks)blocki=++blockj==_nshort_data?_nshort_blocks:0;
        }
      }
    }
  }
}