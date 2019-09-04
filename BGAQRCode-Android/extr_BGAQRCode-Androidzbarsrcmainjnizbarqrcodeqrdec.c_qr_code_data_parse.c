#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_5__ ;
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  qr_pack_buf ;
struct TYPE_9__ {unsigned char* buf; int len; } ;
struct TYPE_8__ {unsigned char sa_index; unsigned char sa_size; unsigned char sa_parity; } ;
struct TYPE_10__ {unsigned int eci; int ai; TYPE_2__ data; TYPE_1__ sa; } ;
struct TYPE_11__ {int mode; TYPE_3__ payload; } ;
typedef  TYPE_4__ qr_code_data_entry ;
struct TYPE_12__ {int nentries; scalar_t__ sa_size; unsigned char sa_index; unsigned char sa_parity; unsigned int self_parity; TYPE_4__* entries; } ;
typedef  TYPE_5__ qr_code_data ;

/* Variables and functions */
 unsigned int* QR_ALNUM_TABLE ; 
#define  QR_MODE_ALNUM 135 
#define  QR_MODE_BYTE 134 
#define  QR_MODE_ECI 133 
#define  QR_MODE_FNC1_1ST 132 
#define  QR_MODE_FNC1_2ND 131 
#define  QR_MODE_KANJI 130 
#define  QR_MODE_NUM 129 
#define  QR_MODE_STRUCT 128 
 scalar_t__ malloc (int) ; 
 int qr_pack_buf_avail (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  qr_pack_buf_init (int /*<<< orphan*/ *,unsigned char const*,int) ; 
 void* qr_pack_buf_read (int /*<<< orphan*/ *,unsigned char const) ; 
 scalar_t__ realloc (TYPE_4__*,int) ; 

__attribute__((used)) static int qr_code_data_parse(qr_code_data *_qrdata,int _version,
 const unsigned char *_data,int _ndata){
  qr_pack_buf qpb;
  unsigned    self_parity;
  int         centries;
  int         len_bits_idx;
  /*Entries are stored directly in the struct during parsing.
    Caller cleans up any allocated data on failure.*/
  _qrdata->entries=NULL;
  _qrdata->nentries=0;
  _qrdata->sa_size=0;
  self_parity=0;
  centries=0;
  /*The versions are divided into 3 ranges that each use a different number of
     bits for length fields.*/
  len_bits_idx=(_version>9)+(_version>26);
  qr_pack_buf_init(&qpb,_data,_ndata);
  /*While we have enough bits to read a mode...*/
  while(qr_pack_buf_avail(&qpb)>=4){
    qr_code_data_entry *entry;
    int                 mode;
    mode=qr_pack_buf_read(&qpb,4);
    /*Mode 0 is a terminator.*/
    if(!mode)break;
    if(_qrdata->nentries>=centries){
      centries=centries<<1|1;
      _qrdata->entries=(qr_code_data_entry *)realloc(_qrdata->entries,
       centries*sizeof(*_qrdata->entries));
    }
    entry=_qrdata->entries+_qrdata->nentries++;
    entry->mode=mode;
    /*Set the buffer to NULL, because if parsing fails, we might try to free it
       on clean-up.*/
    entry->payload.data.buf=NULL;
    switch(mode){
      /*The number of bits used to encode the character count for each version
         range and each data mode.*/
      static const unsigned char LEN_BITS[3][4]={
        {10, 9, 8, 8},
        {12,11,16,10},
        {14,13,16,12}
      };
      case QR_MODE_NUM:{
        unsigned char *buf;
        unsigned       bits;
        unsigned       c;
        int            len;
        int            count;
        int            rem;
        len=qr_pack_buf_read(&qpb,LEN_BITS[len_bits_idx][0]);
        if(len<0)return -1;
        /*Check to see if there are enough bits left now, so we don't have to
           in the decode loop.*/
        count=len/3;
        rem=len%3;
        if(qr_pack_buf_avail(&qpb)<10*count+7*(rem>>1&1)+4*(rem&1))return -1;
        entry->payload.data.buf=buf=(unsigned char *)malloc(len*sizeof(*buf));
        entry->payload.data.len=len;
        /*Read groups of 3 digits encoded in 10 bits.*/
        while(count-->0){
          bits=qr_pack_buf_read(&qpb,10);
          if(bits>=1000)return -1;
          c='0'+bits/100;
          self_parity^=c;
          *buf++=(unsigned char)c;
          bits%=100;
          c='0'+bits/10;
          self_parity^=c;
          *buf++=(unsigned char)c;
          c='0'+bits%10;
          self_parity^=c;
          *buf++=(unsigned char)c;
        }
        /*Read the last two digits encoded in 7 bits.*/
        if(rem>1){
          bits=qr_pack_buf_read(&qpb,7);
          if(bits>=100)return -1;
          c='0'+bits/10;
          self_parity^=c;
          *buf++=(unsigned char)c;
          c='0'+bits%10;
          self_parity^=c;
          *buf++=(unsigned char)c;
        }
        /*Or the last one digit encoded in 4 bits.*/
        else if(rem){
          bits=qr_pack_buf_read(&qpb,4);
          if(bits>=10)return -1;
          c='0'+bits;
          self_parity^=c;
          *buf++=(unsigned char)c;
        }
      }break;
      case QR_MODE_ALNUM:{
        unsigned char *buf;
        unsigned       bits;
        unsigned       c;
        int            len;
        int            count;
        int            rem;
        len=qr_pack_buf_read(&qpb,LEN_BITS[len_bits_idx][1]);
        if(len<0)return -1;
        /*Check to see if there are enough bits left now, so we don't have to
           in the decode loop.*/
        count=len>>1;
        rem=len&1;
        if(qr_pack_buf_avail(&qpb)<11*count+6*rem)return -1;
        entry->payload.data.buf=buf=(unsigned char *)malloc(len*sizeof(*buf));
        entry->payload.data.len=len;
        /*Read groups of two characters encoded in 11 bits.*/
        while(count-->0){
          bits=qr_pack_buf_read(&qpb,11);
          if(bits>=2025)return -1;
          c=QR_ALNUM_TABLE[bits/45];
          self_parity^=c;
          *buf++=(unsigned char)c;
          c=QR_ALNUM_TABLE[bits%45];
          self_parity^=c;
          *buf++=(unsigned char)c;
          len-=2;
        }
        /*Read the last character encoded in 6 bits.*/
        if(rem){
          bits=qr_pack_buf_read(&qpb,6);
          if(bits>=45)return -1;
          c=QR_ALNUM_TABLE[bits];
          self_parity^=c;
          *buf++=(unsigned char)c;
        }
      }break;
      /*Structured-append header.*/
      case QR_MODE_STRUCT:{
        int bits;
        bits=qr_pack_buf_read(&qpb,16);
        if(bits<0)return -1;
        /*We save a copy of the data in _qrdata for easy reference when
           grouping structured-append codes.
          If for some reason the code has multiple S-A headers, first one wins,
           since it is supposed to come before everything else (TODO: should we
           return an error instead?).*/
        if(_qrdata->sa_size==0){
          _qrdata->sa_index=entry->payload.sa.sa_index=
           (unsigned char)(bits>>12&0xF);
          _qrdata->sa_size=entry->payload.sa.sa_size=
           (unsigned char)((bits>>8&0xF)+1);
          _qrdata->sa_parity=entry->payload.sa.sa_parity=
           (unsigned char)(bits&0xFF);
        }
      }break;
      case QR_MODE_BYTE:{
        unsigned char *buf;
        unsigned       c;
        int            len;
        len=qr_pack_buf_read(&qpb,LEN_BITS[len_bits_idx][2]);
        if(len<0)return -1;
        /*Check to see if there are enough bits left now, so we don't have to
           in the decode loop.*/
        if(qr_pack_buf_avail(&qpb)<len<<3)return -1;
        entry->payload.data.buf=buf=(unsigned char *)malloc(len*sizeof(*buf));
        entry->payload.data.len=len;
        while(len-->0){
          c=qr_pack_buf_read(&qpb,8);
          self_parity^=c;
          *buf++=(unsigned char)c;
        }
      }break;
      /*FNC1 first position marker.*/
      case QR_MODE_FNC1_1ST:break;
      /*Extended Channel Interpretation data.*/
      case QR_MODE_ECI:{
        unsigned val;
        int      bits;
        /*ECI uses a variable-width encoding similar to UTF-8*/
        bits=qr_pack_buf_read(&qpb,8);
        if(bits<0)return -1;
        /*One byte:*/
        if(!(bits&0x80))val=bits;
        /*Two bytes:*/
        else if(!(bits&0x40)){
          val=bits&0x3F<<8;
          bits=qr_pack_buf_read(&qpb,8);
          if(bits<0)return -1;
          val|=bits;
        }
        /*Three bytes:*/
        else if(!(bits&0x20)){
          val=bits&0x1F<<16;
          bits=qr_pack_buf_read(&qpb,16);
          if(bits<0)return -1;
          val|=bits;
          /*Valid ECI values are 0...999999.*/
          if(val>=1000000)return -1;
        }
        /*Invalid lead byte.*/
        else return -1;
        entry->payload.eci=val;
      }break;
      case QR_MODE_KANJI:{
        unsigned char *buf;
        unsigned       bits;
        int            len;
        len=qr_pack_buf_read(&qpb,LEN_BITS[len_bits_idx][3]);
        if(len<0)return -1;
        /*Check to see if there are enough bits left now, so we don't have to
           in the decode loop.*/
        if(qr_pack_buf_avail(&qpb)<13*len)return -1;
        entry->payload.data.buf=buf=(unsigned char *)malloc(2*len*sizeof(*buf));
        entry->payload.data.len=2*len;
        /*Decode 2-byte SJIS characters encoded in 13 bits.*/
        while(len-->0){
          bits=qr_pack_buf_read(&qpb,13);
          bits=(bits/0xC0<<8|bits%0xC0)+0x8140;
          if(bits>=0xA000)bits+=0x4000;
          /*TODO: Are values 0xXX7F, 0xXXFD...0xXXFF always invalid?
            Should we reject them here?*/
          self_parity^=bits;
          *buf++=(unsigned char)(bits>>8);
          *buf++=(unsigned char)(bits&0xFF);
        }
      }break;
      /*FNC1 second position marker.*/
      case QR_MODE_FNC1_2ND:{
        int bits;
        /*FNC1 in the 2nd position encodes an Application Indicator in one
           byte, which is either a letter (A...Z or a...z) or a 2-digit number.
          The letters are encoded with their ASCII value plus 100, the numbers
           are encoded directly with their numeric value.
          Values 100...164, 191...196, and 223...255 are invalid, so we reject
           them here.*/
        bits=qr_pack_buf_read(&qpb,8);
        if(!(bits>=0&&bits<100||bits>=165&&bits<191||bits>=197&&bits<223)){
          return -1;
        }
        entry->payload.ai=bits;
      }break;
      /*Unknown mode number:*/
      default:{
        /*Unfortunately, because we have to understand the format of a mode to
           know how many bits it occupies, we can't skip unknown modes.
          Therefore we have to fail.*/
        return -1;
      }break;
    }
  }
  /*Store the parity of the data from this code, for S-A.
    The final parity is the 8-bit XOR of all the decoded bytes of literal data.
    We don't combine the 2-byte kanji codes into one byte in the loops above,
     because we can just do it here instead.*/
  _qrdata->self_parity=((self_parity>>8)^self_parity)&0xFF;
  /*Success.*/
  _qrdata->entries=(qr_code_data_entry *)realloc(_qrdata->entries,
   _qrdata->nentries*sizeof(*_qrdata->entries));
  return 0;
}