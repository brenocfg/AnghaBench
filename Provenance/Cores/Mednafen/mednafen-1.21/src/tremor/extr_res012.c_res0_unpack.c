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
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {int begin; int end; int grouping; int partitions; int groupbook; int* secondstages; int* booklist; int partvals; } ;
typedef  TYPE_2__ vorbis_info_residue0 ;
typedef  TYPE_2__ vorbis_info_residue ;
struct TYPE_11__ {scalar_t__ codec_setup; } ;
typedef  TYPE_4__ vorbis_info ;
typedef  int /*<<< orphan*/  oggpack_buffer ;
struct TYPE_12__ {int books; TYPE_1__** book_param; } ;
typedef  TYPE_5__ codec_setup_info ;
struct TYPE_9__ {scalar_t__ maptype; int entries; int dim; } ;

/* Variables and functions */
 scalar_t__ _ogg_calloc (int,int) ; 
 scalar_t__ icount (int) ; 
 int oggpack_read (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  res0_free_info (TYPE_2__*) ; 

vorbis_info_residue *res0_unpack(vorbis_info *vi,oggpack_buffer *opb){
  int j,acc=0;
  vorbis_info_residue0 *info=(vorbis_info_residue0 *)_ogg_calloc(1,sizeof(*info));
  codec_setup_info     *ci=(codec_setup_info *)vi->codec_setup;

  info->begin=oggpack_read(opb,24);
  info->end=oggpack_read(opb,24);
  info->grouping=oggpack_read(opb,24)+1;
  info->partitions=oggpack_read(opb,6)+1;
  info->groupbook=oggpack_read(opb,8);

  /* check for premature EOP */
  if(info->groupbook<0)goto errout;

  for(j=0;j<info->partitions;j++){
    int cascade=oggpack_read(opb,3);
    int cflag=oggpack_read(opb,1);
    if(cflag<0) goto errout;
    if(cflag){
      int c=oggpack_read(opb,5);
      if(c<0) goto errout;
      cascade|=(c<<3);
    }
    info->secondstages[j]=cascade;

    acc+=icount(cascade);
  }
  for(j=0;j<acc;j++){
    int book=oggpack_read(opb,8);
    if(book<0) goto errout;
    info->booklist[j]=book;
  }

  if(info->groupbook>=ci->books)goto errout;
  for(j=0;j<acc;j++){
    if(info->booklist[j]>=ci->books)goto errout;
    if(ci->book_param[info->booklist[j]]->maptype==0)goto errout;
  }

  /* verify the phrasebook is not specifying an impossible or
     inconsistent partitioning scheme. */
  /* modify the phrasebook ranging check from r16327; an early beta
     encoder had a bug where it used an oversized phrasebook by
     accident.  These files should continue to be playable, but don't
     allow an exploit */
  {
    int entries = ci->book_param[info->groupbook]->entries;
    int dim = ci->book_param[info->groupbook]->dim;
    int partvals = 1;
    if (dim<1) goto errout;
    while(dim>0){
      partvals *= info->partitions;
      if(partvals > entries) goto errout;
      dim--;
    }
    info->partvals = partvals;
  }

  return(info);
 errout:
  res0_free_info(info);
  return(NULL);
}