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
typedef  scalar_t__* qr_point ;
struct TYPE_4__ {int* pos; int extent; } ;
typedef  TYPE_1__ qr_finder_edge_pt ;
struct TYPE_5__ {int* nedge_pts; int* ninliers; int /*<<< orphan*/ * o; TYPE_1__** edge_pts; } ;
typedef  TYPE_2__ qr_finder ;
typedef  int /*<<< orphan*/  qr_aff ;
typedef  int /*<<< orphan*/  isaac_ctx ;

/* Variables and functions */
 int QR_FINDER_SUBPREC ; 
 int abs (scalar_t__) ; 
 int isaac_next_uint (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  qr_aff_unproject (scalar_t__*,int /*<<< orphan*/  const*,int,int) ; 
 int qr_isqrt (int) ; 
 scalar_t__ qr_point_ccw (int*,int*,int*) ; 
 int qr_point_distance2 (int*,int*) ; 
 int /*<<< orphan*/  qr_point_translate (scalar_t__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void qr_finder_ransac(qr_finder *_f,const qr_aff *_hom,
 isaac_ctx *_isaac,int _e){
  qr_finder_edge_pt *edge_pts;
  int                best_ninliers;
  int                n;
  edge_pts=_f->edge_pts[_e];
  n=_f->nedge_pts[_e];
  best_ninliers=0;
  if(n>1){
    int max_iters;
    int i;
    int j;
    /*17 iterations is enough to guarantee an outlier-free sample with more
       than 99% probability given as many as 50% outliers.*/
    max_iters=17;
    for(i=0;i<max_iters;i++){
      qr_point  q0;
      qr_point  q1;
      int       ninliers;
      int       thresh;
      int       p0i;
      int       p1i;
      int      *p0;
      int      *p1;
      int       j;
      /*Pick two random points on this edge.*/
      p0i=isaac_next_uint(_isaac,n);
      p1i=isaac_next_uint(_isaac,n-1);
      if(p1i>=p0i)p1i++;
      p0=edge_pts[p0i].pos;
      p1=edge_pts[p1i].pos;
      /*If the corresponding line is not within 45 degrees of the proper
         orientation in the square domain, reject it outright.
        This can happen, e.g., when highly skewed orientations cause points to
         be misclassified into the wrong edge.
        The irony is that using such points might produce a line which _does_
         pass the corresponding validity checks.*/
      qr_aff_unproject(q0,_hom,p0[0],p0[1]);
      qr_aff_unproject(q1,_hom,p1[0],p1[1]);
      qr_point_translate(q0,-_f->o[0],-_f->o[1]);
      qr_point_translate(q1,-_f->o[0],-_f->o[1]);
      if(abs(q0[_e>>1]-q1[_e>>1])>abs(q0[1-(_e>>1)]-q1[1-(_e>>1)]))continue;
      /*Identify the other edge points which are inliers.
        The squared distance should be distributed as a \Chi^2 distribution
         with one degree of freedom, which means for a 95% confidence the
         point should lie within a factor 3.8414588 ~= 4 times the expected
         variance of the point locations.
        We grossly approximate the standard deviation as 1 pixel in one
         direction, and 0.5 pixels in the other (because we average two
         coordinates).*/
      thresh=qr_isqrt(qr_point_distance2(p0,p1)<<2*QR_FINDER_SUBPREC+1);
      ninliers=0;
      for(j=0;j<n;j++){
        if(abs(qr_point_ccw(p0,p1,edge_pts[j].pos))<=thresh){
          edge_pts[j].extent|=1;
          ninliers++;
        }
        else edge_pts[j].extent&=~1;
      }
      if(ninliers>best_ninliers){
        for(j=0;j<n;j++)edge_pts[j].extent<<=1;
        best_ninliers=ninliers;
        /*The actual number of iterations required is
            log(1-\alpha)/log(1-r*r),
           where \alpha is the required probability of taking a sample with
            no outliers (e.g., 0.99) and r is the estimated ratio of inliers
            (e.g. ninliers/n).
          This is just a rough (but conservative) approximation, but it
           should be good enough to stop the iteration early when we find
           a good set of inliers.*/
        if(ninliers>n>>1)max_iters=(67*n-63*ninliers-1)/(n<<1);
      }
    }
    /*Now collect all the inliers at the beginning of the list.*/
    for(i=j=0;j<best_ninliers;i++)if(edge_pts[i].extent&2){
      if(j<i){
        qr_finder_edge_pt tmp;
        *&tmp=*(edge_pts+i);
        *(edge_pts+j)=*(edge_pts+i);
        *(edge_pts+i)=*&tmp;
      }
      j++;
    }
  }
  _f->ninliers[_e]=best_ninliers;
}