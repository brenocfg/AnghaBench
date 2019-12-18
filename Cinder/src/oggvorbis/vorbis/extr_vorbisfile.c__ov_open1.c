#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {int (* seek_func ) (void*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;} ;
typedef  TYPE_1__ ov_callbacks ;
struct TYPE_11__ {int serialno; } ;
struct TYPE_10__ {int seekable; int links; int* serialnos; int current_serialno; int /*<<< orphan*/  ready_state; int /*<<< orphan*/  offset; int /*<<< orphan*/ * dataoffsets; scalar_t__* offsets; TYPE_4__ os; int /*<<< orphan*/ * datasource; void* vc; void* vi; int /*<<< orphan*/  oy; TYPE_1__ callbacks; } ;
typedef  TYPE_2__ OggVorbis_File ;

/* Variables and functions */
 int /*<<< orphan*/  PARTOPEN ; 
 int /*<<< orphan*/  SEEK_CUR ; 
 int _fetch_headers (TYPE_2__*,void*,void*,long**,int*,int /*<<< orphan*/ *) ; 
 void* _ogg_calloc (int,int) ; 
 int /*<<< orphan*/  _ogg_free (long*) ; 
 int /*<<< orphan*/  memcpy (char*,...) ; 
 int /*<<< orphan*/  memset (TYPE_2__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ogg_stream_init (TYPE_4__*,int) ; 
 char* ogg_sync_buffer (int /*<<< orphan*/ *,long) ; 
 int /*<<< orphan*/  ogg_sync_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ogg_sync_wrote (int /*<<< orphan*/ *,long) ; 
 int /*<<< orphan*/  ov_clear (TYPE_2__*) ; 
 int stub1 (void*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int _ov_open1(void *f,OggVorbis_File *vf,const char *initial,
                     long ibytes, ov_callbacks callbacks){
  int offsettest=((f && callbacks.seek_func)?callbacks.seek_func(f,0,SEEK_CUR):-1);
  long *serialno_list=NULL;
  int serialno_list_size=0;
  int ret;

  memset(vf,0,sizeof(*vf));
  vf->datasource=f;
  vf->callbacks = callbacks;

  /* init the framing state */
  ogg_sync_init(&vf->oy);

  /* perhaps some data was previously read into a buffer for testing
     against other stream types.  Allow initialization from this
     previously read data (especially as we may be reading from a
     non-seekable stream) */
  if(initial){
    char *buffer=ogg_sync_buffer(&vf->oy,ibytes);
    memcpy(buffer,initial,ibytes);
    ogg_sync_wrote(&vf->oy,ibytes);
  }

  /* can we seek? Stevens suggests the seek test was portable */
  if(offsettest!=-1)vf->seekable=1;

  /* No seeking yet; Set up a 'single' (current) logical bitstream
     entry for partial open */
  vf->links=1;
  vf->vi=_ogg_calloc(vf->links,sizeof(*vf->vi));
  vf->vc=_ogg_calloc(vf->links,sizeof(*vf->vc));
  ogg_stream_init(&vf->os,-1); /* fill in the serialno later */

  /* Fetch all BOS pages, store the vorbis header and all seen serial
     numbers, load subsequent vorbis setup headers */
  if((ret=_fetch_headers(vf,vf->vi,vf->vc,&serialno_list,&serialno_list_size,NULL))<0){
    vf->datasource=NULL;
    ov_clear(vf);
  }else{
    /* serial number list for first link needs to be held somewhere
       for second stage of seekable stream open; this saves having to
       seek/reread first link's serialnumber data then. */
    vf->serialnos=_ogg_calloc(serialno_list_size+2,sizeof(*vf->serialnos));
    vf->serialnos[0]=vf->current_serialno=vf->os.serialno;
    vf->serialnos[1]=serialno_list_size;
    memcpy(vf->serialnos+2,serialno_list,serialno_list_size*sizeof(*vf->serialnos));

    vf->offsets=_ogg_calloc(1,sizeof(*vf->offsets));
    vf->dataoffsets=_ogg_calloc(1,sizeof(*vf->dataoffsets));
    vf->offsets[0]=0;
    vf->dataoffsets[0]=vf->offset;

    vf->ready_state=PARTOPEN;
  }
  if(serialno_list)_ogg_free(serialno_list);
  return(ret);
}