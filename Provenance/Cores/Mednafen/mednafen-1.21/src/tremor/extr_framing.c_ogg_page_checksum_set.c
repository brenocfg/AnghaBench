#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int ogg_uint32_t ;
struct TYPE_3__ {int* header; int header_len; int body_len; int* body; } ;
typedef  TYPE_1__ ogg_page ;

/* Variables and functions */
 int* crc_lookup ; 

void ogg_page_checksum_set(ogg_page *og){
  if(og){
    ogg_uint32_t crc_reg=0;
    int i;

    /* safety; needed for API behavior, but not framing code */
    og->header[22]=0;
    og->header[23]=0;
    og->header[24]=0;
    og->header[25]=0;

    for(i=0;i<og->header_len;i++)
      crc_reg=(crc_reg<<8)^crc_lookup[((crc_reg >> 24)&0xff)^og->header[i]];
    for(i=0;i<og->body_len;i++)
      crc_reg=(crc_reg<<8)^crc_lookup[((crc_reg >> 24)&0xff)^og->body[i]];

    og->header[22]=(unsigned char)(crc_reg&0xff);
    og->header[23]=(unsigned char)((crc_reg>>8)&0xff);
    og->header[24]=(unsigned char)((crc_reg>>16)&0xff);
    og->header[25]=(unsigned char)((crc_reg>>24)&0xff);
  }
}