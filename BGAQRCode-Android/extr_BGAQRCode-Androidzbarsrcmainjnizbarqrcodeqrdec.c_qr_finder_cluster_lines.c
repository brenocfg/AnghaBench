#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int len; scalar_t__* pos; scalar_t__ boffs; scalar_t__ eoffs; } ;
typedef  TYPE_1__ qr_finder_line ;
struct TYPE_7__ {int nlines; TYPE_1__** lines; } ;
typedef  TYPE_2__ qr_finder_cluster ;

/* Variables and functions */
 int QR_FINDER_SUBPREC ; 
 int abs (scalar_t__) ; 
 scalar_t__ calloc (int,int) ; 
 int /*<<< orphan*/  free (unsigned char*) ; 

__attribute__((used)) static int qr_finder_cluster_lines(qr_finder_cluster *_clusters,
 qr_finder_line **_neighbors,qr_finder_line *_lines,int _nlines,int _v){
  unsigned char   *mark;
  qr_finder_line **neighbors;
  int              nneighbors;
  int              nclusters;
  int              i;
  /*TODO: Kalman filters!*/
  mark=(unsigned char *)calloc(_nlines,sizeof(*mark));
  neighbors=_neighbors;
  nclusters=0;
  for(i=0;i<_nlines-1;i++)if(!mark[i]){
    int len;
    int j;
    nneighbors=1;
    neighbors[0]=_lines+i;
    len=_lines[i].len;
    for(j=i+1;j<_nlines;j++)if(!mark[j]){
      const qr_finder_line *a;
      const qr_finder_line *b;
      int                   thresh;
      a=neighbors[nneighbors-1];
      b=_lines+j;
      /*The clustering threshold is proportional to the size of the lines,
         since minor noise in large areas can interrupt patterns more easily
         at high resolutions.*/
      thresh=a->len+7>>2;
      if(abs(a->pos[1-_v]-b->pos[1-_v])>thresh)break;
      if(abs(a->pos[_v]-b->pos[_v])>thresh)continue;
      if(abs(a->pos[_v]+a->len-b->pos[_v]-b->len)>thresh)continue;
      if(a->boffs>0&&b->boffs>0&&
       abs(a->pos[_v]-a->boffs-b->pos[_v]+b->boffs)>thresh){
        continue;
      }
      if(a->eoffs>0&&b->eoffs>0&&
       abs(a->pos[_v]+a->len+a->eoffs-b->pos[_v]-b->len-b->eoffs)>thresh){
        continue;
      }
      neighbors[nneighbors++]=_lines+j;
      len+=b->len;
    }
    /*We require at least three lines to form a cluster, which eliminates a
       large number of false positives, saving considerable decoding time.
      This should still be sufficient for 1-pixel codes with no noise.*/
    if(nneighbors<3)continue;
    /*The expected number of lines crossing a finder pattern is equal to their
       average length.
      We accept the cluster if size is at least 1/3 their average length (this
       is a very small threshold, but was needed for some test images).*/
    len=((len<<1)+nneighbors)/(nneighbors<<1);
    if(nneighbors*(5<<QR_FINDER_SUBPREC)>=len){
      _clusters[nclusters].lines=neighbors;
      _clusters[nclusters].nlines=nneighbors;
      for(j=0;j<nneighbors;j++)mark[neighbors[j]-_lines]=1;
      neighbors+=nneighbors;
      nclusters++;
    }
  }
  free(mark);
  return nclusters;
}