#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {long n; long posts; long* sorted_index; int* reverse_index; int* loneighbor; int* hineighbor; TYPE_2__* vi; } ;
typedef  TYPE_1__ vorbis_look_floor1 ;
struct TYPE_8__ {int* postlist; } ;
typedef  TYPE_2__ vorbis_info_floor1 ;
typedef  int /*<<< orphan*/  vorbis_block ;
typedef  int /*<<< orphan*/  lsfit_acc ;

/* Variables and functions */
 int /*<<< orphan*/  VIF_POSIT ; 
 int* _vorbis_block_alloc (int /*<<< orphan*/ *,int) ; 
 scalar_t__ accumulate_fit (float const*,float const*,long,long,int /*<<< orphan*/ *,long,TYPE_2__*) ; 
 int /*<<< orphan*/  exit (int) ; 
 int fit_line (int /*<<< orphan*/ *,int,int*,int*,TYPE_2__*) ; 
 scalar_t__ inspect_error (int,int,int,int,float const*,float const*,TYPE_2__*) ; 
 int post_Y (int*,int*,long) ; 
 int render_point (int,int,int,int,int) ; 

int *floor1_fit(vorbis_block *vb,vorbis_look_floor1 *look,
                          const float *logmdct,   /* in */
                          const float *logmask){
  long i,j;
  vorbis_info_floor1 *info=look->vi;
  long n=look->n;
  long posts=look->posts;
  long nonzero=0;
  lsfit_acc fits[VIF_POSIT+1];
  int fit_valueA[VIF_POSIT+2]; /* index by range list position */
  int fit_valueB[VIF_POSIT+2]; /* index by range list position */

  int loneighbor[VIF_POSIT+2]; /* sorted index of range list position (+2) */
  int hineighbor[VIF_POSIT+2];
  int *output=NULL;
  int memo[VIF_POSIT+2];

  for(i=0;i<posts;i++)fit_valueA[i]=-200; /* mark all unused */
  for(i=0;i<posts;i++)fit_valueB[i]=-200; /* mark all unused */
  for(i=0;i<posts;i++)loneighbor[i]=0; /* 0 for the implicit 0 post */
  for(i=0;i<posts;i++)hineighbor[i]=1; /* 1 for the implicit post at n */
  for(i=0;i<posts;i++)memo[i]=-1;      /* no neighbor yet */

  /* quantize the relevant floor points and collect them into line fit
     structures (one per minimal division) at the same time */
  if(posts==0){
    nonzero+=accumulate_fit(logmask,logmdct,0,n,fits,n,info);
  }else{
    for(i=0;i<posts-1;i++)
      nonzero+=accumulate_fit(logmask,logmdct,look->sorted_index[i],
                              look->sorted_index[i+1],fits+i,
                              n,info);
  }

  if(nonzero){
    /* start by fitting the implicit base case.... */
    int y0=-200;
    int y1=-200;
    fit_line(fits,posts-1,&y0,&y1,info);

    fit_valueA[0]=y0;
    fit_valueB[0]=y0;
    fit_valueB[1]=y1;
    fit_valueA[1]=y1;

    /* Non degenerate case */
    /* start progressive splitting.  This is a greedy, non-optimal
       algorithm, but simple and close enough to the best
       answer. */
    for(i=2;i<posts;i++){
      int sortpos=look->reverse_index[i];
      int ln=loneighbor[sortpos];
      int hn=hineighbor[sortpos];

      /* eliminate repeat searches of a particular range with a memo */
      if(memo[ln]!=hn){
        /* haven't performed this error search yet */
        int lsortpos=look->reverse_index[ln];
        int hsortpos=look->reverse_index[hn];
        memo[ln]=hn;

        {
          /* A note: we want to bound/minimize *local*, not global, error */
          int lx=info->postlist[ln];
          int hx=info->postlist[hn];
          int ly=post_Y(fit_valueA,fit_valueB,ln);
          int hy=post_Y(fit_valueA,fit_valueB,hn);

          if(ly==-1 || hy==-1){
            exit(1);
          }

          if(inspect_error(lx,hx,ly,hy,logmask,logmdct,info)){
            /* outside error bounds/begin search area.  Split it. */
            int ly0=-200;
            int ly1=-200;
            int hy0=-200;
            int hy1=-200;
            int ret0=fit_line(fits+lsortpos,sortpos-lsortpos,&ly0,&ly1,info);
            int ret1=fit_line(fits+sortpos,hsortpos-sortpos,&hy0,&hy1,info);

            if(ret0){
              ly0=ly;
              ly1=hy0;
            }
            if(ret1){
              hy0=ly1;
              hy1=hy;
            }

            if(ret0 && ret1){
              fit_valueA[i]=-200;
              fit_valueB[i]=-200;
            }else{
              /* store new edge values */
              fit_valueB[ln]=ly0;
              if(ln==0)fit_valueA[ln]=ly0;
              fit_valueA[i]=ly1;
              fit_valueB[i]=hy0;
              fit_valueA[hn]=hy1;
              if(hn==1)fit_valueB[hn]=hy1;

              if(ly1>=0 || hy0>=0){
                /* store new neighbor values */
                for(j=sortpos-1;j>=0;j--)
                  if(hineighbor[j]==hn)
                    hineighbor[j]=i;
                  else
                    break;
                for(j=sortpos+1;j<posts;j++)
                  if(loneighbor[j]==ln)
                    loneighbor[j]=i;
                  else
                    break;
              }
            }
          }else{
            fit_valueA[i]=-200;
            fit_valueB[i]=-200;
          }
        }
      }
    }

    output=_vorbis_block_alloc(vb,sizeof(*output)*posts);

    output[0]=post_Y(fit_valueA,fit_valueB,0);
    output[1]=post_Y(fit_valueA,fit_valueB,1);

    /* fill in posts marked as not using a fit; we will zero
       back out to 'unused' when encoding them so long as curve
       interpolation doesn't force them into use */
    for(i=2;i<posts;i++){
      int ln=look->loneighbor[i-2];
      int hn=look->hineighbor[i-2];
      int x0=info->postlist[ln];
      int x1=info->postlist[hn];
      int y0=output[ln];
      int y1=output[hn];

      int predicted=render_point(x0,x1,y0,y1,info->postlist[i]);
      int vx=post_Y(fit_valueA,fit_valueB,i);

      if(vx>=0 && predicted!=vx){
        output[i]=vx;
      }else{
        output[i]= predicted|0x8000;
      }
    }
  }

  return(output);

}