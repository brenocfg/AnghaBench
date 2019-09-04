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
 int /*<<< orphan*/  memset (unsigned int*,int,int) ; 

__attribute__((used)) static void qr_data_mask_fill(unsigned *_mask,int _dim,int _pattern){
  int stride;
  int i;
  int j;
  stride=_dim+QR_INT_BITS-1>>QR_INT_LOGBITS;
  /*Note that we store bits column-wise, since that's how they're read out of
     the grid.*/
  switch(_pattern){
    /*10101010 i+j+1&1
      01010101
      10101010
      01010101*/
    case 0:{
      int m;
      m=0x55;
      for(j=0;j<_dim;j++){
        memset(_mask+j*stride,m,stride*sizeof(*_mask));
        m^=0xFF;
      }
    }break;
    /*11111111 i+1&1
      00000000
      11111111
      00000000*/
    case 1:memset(_mask,0x55,_dim*stride*sizeof(*_mask));break;
    /*10010010 (j+1)%3&1
      10010010
      10010010
      10010010*/
    case 2:{
      unsigned m;
      m=0xFF;
      for(j=0;j<_dim;j++){
        memset(_mask+j*stride,m&0xFF,stride*sizeof(*_mask));
        m=m<<8|m>>16;
      }
    }break;
    /*10010010 (i+j+1)%3&1
      00100100
      01001001
      10010010*/
    case 3:{
      unsigned mi;
      unsigned mj;
      mj=0;
      for(i=0;i<(QR_INT_BITS+2)/3;i++)mj|=1<<3*i;
      for(j=0;j<_dim;j++){
        mi=mj;
        for(i=0;i<stride;i++){
          _mask[j*stride+i]=mi;
          mi=mi>>QR_INT_BITS%3|mi<<3-QR_INT_BITS%3;
        }
        mj=mj>>1|mj<<2;
      }
    }break;
    /*11100011 (i>>1)+(j/3)+1&1
      11100011
      00011100
      00011100*/
    case 4:{
      unsigned m;
      m=7;
      for(j=0;j<_dim;j++){
        memset(_mask+j*stride,(0xCC^-(m&1))&0xFF,stride*sizeof(*_mask));
        m=m>>1|m<<5;
      }
    }break;
    /*11111111 !((i*j)%6)
      10000010
      10010010
      10101010*/
    case 5:{
      for(j=0;j<_dim;j++){
        unsigned m;
        m=0;
        for(i=0;i<6;i++)m|=!((i*j)%6)<<i;
        for(i=6;i<QR_INT_BITS;i<<=1)m|=m<<i;
        for(i=0;i<stride;i++){
          _mask[j*stride+i]=m;
          m=m>>QR_INT_BITS%6|m<<6-QR_INT_BITS%6;
        }
      }
    }break;
    /*11111111 (i*j)%3+i*j+1&1
      11100011
      11011011
      10101010*/
    case 6:{
      for(j=0;j<_dim;j++){
        unsigned m;
        m=0;
        for(i=0;i<6;i++)m|=((i*j)%3+i*j+1&1)<<i;
        for(i=6;i<QR_INT_BITS;i<<=1)m|=m<<i;
        for(i=0;i<stride;i++){
          _mask[j*stride+i]=m;
          m=m>>QR_INT_BITS%6|m<<6-QR_INT_BITS%6;
        }
      }
    }break;
    /*10101010 (i*j)%3+i+j+1&1
      00011100
      10001110
      01010101*/
    default:{
      for(j=0;j<_dim;j++){
        unsigned m;
        m=0;
        for(i=0;i<6;i++)m|=((i*j)%3+i+j+1&1)<<i;
        for(i=6;i<QR_INT_BITS;i<<=1)m|=m<<i;
        for(i=0;i<stride;i++){
          _mask[j*stride+i]=m;
          m=m>>QR_INT_BITS%6|m<<6-QR_INT_BITS%6;
        }
      }
    }break;
  }
}