#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_4__ ;
typedef  struct TYPE_13__   TYPE_3__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
struct TYPE_11__ {int /*<<< orphan*/ * codec_setup; int /*<<< orphan*/  rate; } ;
typedef  TYPE_1__ vorbis_info ;
struct TYPE_12__ {int /*<<< orphan*/ * vendor; } ;
typedef  TYPE_2__ vorbis_comment ;
typedef  int /*<<< orphan*/  oggpack_buffer ;
struct TYPE_13__ {int /*<<< orphan*/  b_o_s; int /*<<< orphan*/  bytes; int /*<<< orphan*/  packet; } ;
typedef  TYPE_3__ ogg_packet ;
struct TYPE_14__ {int /*<<< orphan*/  books; } ;
typedef  TYPE_4__ codec_setup_info ;

/* Variables and functions */
 int OV_EBADHEADER ; 
 int OV_EFAULT ; 
 int OV_ENOTVORBIS ; 
 int /*<<< orphan*/  _v_readstring (int /*<<< orphan*/ *,char*,int) ; 
 int _vorbis_unpack_books (TYPE_1__*,int /*<<< orphan*/ *) ; 
 int _vorbis_unpack_comment (TYPE_2__*,int /*<<< orphan*/ *) ; 
 int _vorbis_unpack_info (TYPE_1__*,int /*<<< orphan*/ *) ; 
 scalar_t__ memcmp (char*,char*,int) ; 
 int /*<<< orphan*/  memset (char*,int /*<<< orphan*/ ,int) ; 
 int oggpack_read (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  oggpack_readinit (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int vorbis_synthesis_headerin(vorbis_info *vi,vorbis_comment *vc,ogg_packet *op){
  oggpack_buffer opb;
  
  if(op){
    oggpack_readinit(&opb,op->packet,op->bytes);

    /* Which of the three types of header is this? */
    /* Also verify header-ness, vorbis */
    {
      char buffer[6];
      int packtype=oggpack_read(&opb,8);
      memset(buffer,0,6);
      _v_readstring(&opb,buffer,6);
      if(memcmp(buffer,"vorbis",6)){
	/* not a vorbis header */
	return(OV_ENOTVORBIS);
      }
      switch(packtype){
      case 0x01: /* least significant *bit* is read first */
	if(!op->b_o_s){
	  /* Not the initial packet */
	  return(OV_EBADHEADER);
	}
	if(vi->rate!=0){
	  /* previously initialized info header */
	  return(OV_EBADHEADER);
	}

	return(_vorbis_unpack_info(vi,&opb));

      case 0x03: /* least significant *bit* is read first */
	if(vi->rate==0){
	  /* um... we didn't get the initial header */
	  return(OV_EBADHEADER);
	}
        if(vc->vendor!=NULL){
          /* previously initialized comment header */
          return(OV_EBADHEADER);
        }

	return(_vorbis_unpack_comment(vc,&opb));

      case 0x05: /* least significant *bit* is read first */
	if(vi->rate==0 || vc->vendor==NULL){
	  /* um... we didn;t get the initial header or comments yet */
	  return(OV_EBADHEADER);
	}
        if(vi->codec_setup==NULL){
          /* improperly initialized vorbis_info */
          return(OV_EFAULT);
        }
        if(((codec_setup_info *)vi->codec_setup)->books>0){
          /* previously initialized setup header */
          return(OV_EBADHEADER);
        }

	return(_vorbis_unpack_books(vi,&opb));

      default:
	/* Not a valid vorbis header type */
	return(OV_EBADHEADER);
	break;
      }
    }
  }
  return(OV_EBADHEADER);
}