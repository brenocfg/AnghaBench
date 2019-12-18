#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_19__   TYPE_8__ ;
typedef  struct TYPE_18__   TYPE_7__ ;
typedef  struct TYPE_17__   TYPE_6__ ;
typedef  struct TYPE_16__   TYPE_5__ ;
typedef  struct TYPE_15__   TYPE_4__ ;
typedef  struct TYPE_14__   TYPE_3__ ;
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;

/* Type definitions */
struct TYPE_14__ {long posts; int* loneighbor; int* hineighbor; int quant_q; int postbits; int* forward_index; int /*<<< orphan*/  phrasebits; int /*<<< orphan*/  frames; TYPE_4__* vi; } ;
typedef  TYPE_3__ vorbis_look_floor1 ;
struct TYPE_15__ {int mult; int* postlist; long partitions; int* partitionclass; int* class_dim; int* class_subs; int** class_subbook; int* class_book; } ;
typedef  TYPE_4__ vorbis_info_floor1 ;
struct TYPE_16__ {int pcmend; size_t W; TYPE_2__* vd; } ;
typedef  TYPE_5__ vorbis_block ;
struct TYPE_17__ {int entries; } ;
typedef  TYPE_6__ static_codebook ;
typedef  int /*<<< orphan*/  oggpack_buffer ;
struct TYPE_18__ {int* blocksizes; TYPE_8__* fullbooks; TYPE_6__** book_param; } ;
typedef  TYPE_7__ codec_setup_info ;
struct TYPE_19__ {int entries; } ;
typedef  TYPE_8__ codebook ;
struct TYPE_13__ {TYPE_1__* vi; } ;
struct TYPE_12__ {TYPE_7__* codec_setup; } ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int /*<<< orphan*/  VIF_POSIT ; 
 int /*<<< orphan*/  fclose (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * fopen (char*,char*) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ *,char*,int) ; 
 int ilog (int) ; 
 int /*<<< orphan*/  memset (int*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  oggpack_write (int /*<<< orphan*/ *,int,int) ; 
 int /*<<< orphan*/  render_line0 (int,int,int,int,int,int*) ; 
 int render_point (int,int,int,int,int) ; 
 int /*<<< orphan*/  sprintf (char*,char*,int,long,int,...) ; 
 scalar_t__ vorbis_book_encode (TYPE_8__*,int,int /*<<< orphan*/ *) ; 

int floor1_encode(oggpack_buffer *opb,vorbis_block *vb,
                  vorbis_look_floor1 *look,
                  int *post,int *ilogmask){

  long i,j;
  vorbis_info_floor1 *info=look->vi;
  long posts=look->posts;
  codec_setup_info *ci=vb->vd->vi->codec_setup;
  int out[VIF_POSIT+2];
  static_codebook **sbooks=ci->book_param;
  codebook *books=ci->fullbooks;

  /* quantize values to multiplier spec */
  if(post){
    for(i=0;i<posts;i++){
      int val=post[i]&0x7fff;
      switch(info->mult){
      case 1: /* 1024 -> 256 */
        val>>=2;
        break;
      case 2: /* 1024 -> 128 */
        val>>=3;
        break;
      case 3: /* 1024 -> 86 */
        val/=12;
        break;
      case 4: /* 1024 -> 64 */
        val>>=4;
        break;
      }
      post[i]=val | (post[i]&0x8000);
    }

    out[0]=post[0];
    out[1]=post[1];

    /* find prediction values for each post and subtract them */
    for(i=2;i<posts;i++){
      int ln=look->loneighbor[i-2];
      int hn=look->hineighbor[i-2];
      int x0=info->postlist[ln];
      int x1=info->postlist[hn];
      int y0=post[ln];
      int y1=post[hn];

      int predicted=render_point(x0,x1,y0,y1,info->postlist[i]);

      if((post[i]&0x8000) || (predicted==post[i])){
        post[i]=predicted|0x8000; /* in case there was roundoff jitter
                                     in interpolation */
        out[i]=0;
      }else{
        int headroom=(look->quant_q-predicted<predicted?
                      look->quant_q-predicted:predicted);

        int val=post[i]-predicted;

        /* at this point the 'deviation' value is in the range +/- max
           range, but the real, unique range can always be mapped to
           only [0-maxrange).  So we want to wrap the deviation into
           this limited range, but do it in the way that least screws
           an essentially gaussian probability distribution. */

        if(val<0)
          if(val<-headroom)
            val=headroom-val-1;
          else
            val=-1-(val<<1);
        else
          if(val>=headroom)
            val= val+headroom;
          else
            val<<=1;

        out[i]=val;
        post[ln]&=0x7fff;
        post[hn]&=0x7fff;
      }
    }

    /* we have everything we need. pack it out */
    /* mark nontrivial floor */
    oggpack_write(opb,1,1);

    /* beginning/end post */
    look->frames++;
    look->postbits+=ilog(look->quant_q-1)*2;
    oggpack_write(opb,out[0],ilog(look->quant_q-1));
    oggpack_write(opb,out[1],ilog(look->quant_q-1));


    /* partition by partition */
    for(i=0,j=2;i<info->partitions;i++){
      int class=info->partitionclass[i];
      int cdim=info->class_dim[class];
      int csubbits=info->class_subs[class];
      int csub=1<<csubbits;
      int bookas[8]={0,0,0,0,0,0,0,0};
      int cval=0;
      int cshift=0;
      int k,l;

      /* generate the partition's first stage cascade value */
      if(csubbits){
        int maxval[8];
        for(k=0;k<csub;k++){
          int booknum=info->class_subbook[class][k];
          if(booknum<0){
            maxval[k]=1;
          }else{
            maxval[k]=sbooks[info->class_subbook[class][k]]->entries;
          }
        }
        for(k=0;k<cdim;k++){
          for(l=0;l<csub;l++){
            int val=out[j+k];
            if(val<maxval[l]){
              bookas[k]=l;
              break;
            }
          }
          cval|= bookas[k]<<cshift;
          cshift+=csubbits;
        }
        /* write it */
        look->phrasebits+=
          vorbis_book_encode(books+info->class_book[class],cval,opb);

#ifdef TRAIN_FLOOR1
        {
          FILE *of;
          char buffer[80];
          sprintf(buffer,"line_%dx%ld_class%d.vqd",
                  vb->pcmend/2,posts-2,class);
          of=fopen(buffer,"a");
          fprintf(of,"%d\n",cval);
          fclose(of);
        }
#endif
      }

      /* write post values */
      for(k=0;k<cdim;k++){
        int book=info->class_subbook[class][bookas[k]];
        if(book>=0){
          /* hack to allow training with 'bad' books */
          if(out[j+k]<(books+book)->entries)
            look->postbits+=vorbis_book_encode(books+book,
                                               out[j+k],opb);
          /*else
            fprintf(stderr,"+!");*/

#ifdef TRAIN_FLOOR1
          {
            FILE *of;
            char buffer[80];
            sprintf(buffer,"line_%dx%ld_%dsub%d.vqd",
                    vb->pcmend/2,posts-2,class,bookas[k]);
            of=fopen(buffer,"a");
            fprintf(of,"%d\n",out[j+k]);
            fclose(of);
          }
#endif
        }
      }
      j+=cdim;
    }

    {
      /* generate quantized floor equivalent to what we'd unpack in decode */
      /* render the lines */
      int hx=0;
      int lx=0;
      int ly=post[0]*info->mult;
      int n=ci->blocksizes[vb->W]/2;

      for(j=1;j<look->posts;j++){
        int current=look->forward_index[j];
        int hy=post[current]&0x7fff;
        if(hy==post[current]){

          hy*=info->mult;
          hx=info->postlist[current];

          render_line0(n,lx,hx,ly,hy,ilogmask);

          lx=hx;
          ly=hy;
        }
      }
      for(j=hx;j<vb->pcmend/2;j++)ilogmask[j]=ly; /* be certain */
      return(1);
    }
  }else{
    oggpack_write(opb,0,1);
    memset(ilogmask,0,vb->pcmend/2*sizeof(*ilogmask));
    return(0);
  }
}