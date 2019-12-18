#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_5__ ;
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
struct TYPE_11__ {int order; int rate; int barkmap; int numbooks; size_t* books; void* ampdB; void* ampbits; } ;
typedef  TYPE_2__ vorbis_info_floor0 ;
typedef  TYPE_2__ vorbis_info_floor ;
struct TYPE_12__ {TYPE_5__* codec_setup; } ;
typedef  TYPE_4__ vorbis_info ;
typedef  int /*<<< orphan*/  oggpack_buffer ;
struct TYPE_13__ {size_t books; TYPE_1__** book_param; } ;
typedef  TYPE_5__ codec_setup_info ;
struct TYPE_10__ {scalar_t__ maptype; int dim; } ;

/* Variables and functions */
 TYPE_2__* _ogg_malloc (int) ; 
 int /*<<< orphan*/  floor0_free_info (TYPE_2__*) ; 
 void* oggpack_read (int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static vorbis_info_floor *floor0_unpack (vorbis_info *vi,oggpack_buffer *opb){
  codec_setup_info     *ci=vi->codec_setup;
  int j;

  vorbis_info_floor0 *info=_ogg_malloc(sizeof(*info));
  info->order=oggpack_read(opb,8);
  info->rate=oggpack_read(opb,16);
  info->barkmap=oggpack_read(opb,16);
  info->ampbits=oggpack_read(opb,6);
  info->ampdB=oggpack_read(opb,8);
  info->numbooks=oggpack_read(opb,4)+1;

  if(info->order<1)goto err_out;
  if(info->rate<1)goto err_out;
  if(info->barkmap<1)goto err_out;
  if(info->numbooks<1)goto err_out;

  for(j=0;j<info->numbooks;j++){
    info->books[j]=oggpack_read(opb,8);
    if(info->books[j]<0 || info->books[j]>=ci->books)goto err_out;
    if(ci->book_param[info->books[j]]->maptype==0)goto err_out;
    if(ci->book_param[info->books[j]]->dim<1)goto err_out;
  }
  return(info);

 err_out:
  floor0_free_info(info);
  return(NULL);
}