#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int* qr_point ;
struct TYPE_4__ {scalar_t__ extent; } ;
typedef  TYPE_1__ qr_finder_edge_pt ;
struct TYPE_5__ {scalar_t__* nedge_pts; int* o; int* size; int* eversion; TYPE_1__** edge_pts; } ;
typedef  TYPE_2__ qr_finder ;

/* Variables and functions */
 int QR_DIVROUND (int,int) ; 
 int QR_LARGE_VERSION_SLACK ; 
 int abs (int) ; 

__attribute__((used)) static int qr_finder_estimate_module_size_and_version(qr_finder *_f,
 int _width,int _height){
  qr_point offs;
  int      sums[4];
  int      nsums[4];
  int      usize;
  int      nusize;
  int      vsize;
  int      nvsize;
  int      uversion;
  int      vversion;
  int      e;
  offs[0]=offs[1]=0;
  for(e=0;e<4;e++)if(_f->nedge_pts[e]>0){
    qr_finder_edge_pt *edge_pts;
    int                sum;
    int                mean;
    int                n;
    int                i;
    /*Average the samples for this edge, dropping the top and bottom 25%.*/
    edge_pts=_f->edge_pts[e];
    n=_f->nedge_pts[e];
    sum=0;
    for(i=(n>>2);i<n-(n>>2);i++)sum+=edge_pts[i].extent;
    n=n-((n>>2)<<1);
    mean=QR_DIVROUND(sum,n);
    offs[e>>1]+=mean;
    sums[e]=sum;
    nsums[e]=n;
  }
  else nsums[e]=sums[e]=0;
  /*If we have samples on both sides of an axis, refine our idea of where the
     unprojected finder center is located.*/
  if(_f->nedge_pts[0]>0&&_f->nedge_pts[1]>0){
    _f->o[0]-=offs[0]>>1;
    sums[0]-=offs[0]*nsums[0]>>1;
    sums[1]-=offs[0]*nsums[1]>>1;
  }
  if(_f->nedge_pts[2]>0&&_f->nedge_pts[3]>0){
    _f->o[1]-=offs[1]>>1;
    sums[2]-=offs[1]*nsums[2]>>1;
    sums[3]-=offs[1]*nsums[3]>>1;
  }
  /*We must have _some_ samples along each axis... if we don't, our transform
     must be pretty severely distorting the original square (e.g., with
     coordinates so large as to cause overflow).*/
  nusize=nsums[0]+nsums[1];
  if(nusize<=0)return -1;
  /*The module size is 1/3 the average edge extent.*/
  nusize*=3;
  usize=sums[1]-sums[0];
  usize=((usize<<1)+nusize)/(nusize<<1);
  if(usize<=0)return -1;
  /*Now estimate the version directly from the module size and the distance
     between the finder patterns.
    This is done independently using the extents along each axis.
    If either falls significantly outside the valid range (1 to 40), reject the
     configuration.*/
  uversion=(_width-8*usize)/(usize<<2);
  if(uversion<1||uversion>40+QR_LARGE_VERSION_SLACK)return -1;
  /*Now do the same for the other axis.*/
  nvsize=nsums[2]+nsums[3];
  if(nvsize<=0)return -1;
  nvsize*=3;
  vsize=sums[3]-sums[2];
  vsize=((vsize<<1)+nvsize)/(nvsize<<1);
  if(vsize<=0)return -1;
  vversion=(_height-8*vsize)/(vsize<<2);
  if(vversion<1||vversion>40+QR_LARGE_VERSION_SLACK)return -1;
  /*If the estimated version using extents along one axis is significantly
     different than the estimated version along the other axis, then the axes
     have significantly different scalings (relative to the grid).
    This can happen, e.g., when we have multiple adjacent QR codes, and we've
     picked two finder patterns from one and the third finder pattern from
     another, e.g.:
      X---DL UL---X
      |....   |....
      X....  UR....
    Such a configuration might even pass any other geometric checks if we
     didn't reject it here.*/
  if(abs(uversion-vversion)>QR_LARGE_VERSION_SLACK)return -1;
  _f->size[0]=usize;
  _f->size[1]=vsize;
  /*We intentionally do not compute an average version from the sizes along
     both axes.
    In the presence of projective distortion, one of them will be much more
     accurate than the other.*/
  _f->eversion[0]=uversion;
  _f->eversion[1]=vversion;
  return 0;
}