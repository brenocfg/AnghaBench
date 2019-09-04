#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  int* qr_point ;
typedef  int /*<<< orphan*/  qr_line ;
struct TYPE_10__ {int* pos; } ;
typedef  TYPE_2__ qr_finder_edge_pt ;
struct TYPE_11__ {int* ninliers; int* o; int* size; TYPE_1__* c; TYPE_2__** edge_pts; } ;
typedef  TYPE_3__ qr_finder ;
struct TYPE_12__ {int /*<<< orphan*/  res; } ;
typedef  TYPE_4__ qr_aff ;
struct TYPE_9__ {int /*<<< orphan*/ * pos; } ;

/* Variables and functions */
 int QR_MAXI (int,int) ; 
 int /*<<< orphan*/  free (int**) ; 
 scalar_t__ malloc (int) ; 
 int /*<<< orphan*/  qr_aff_project (int*,TYPE_4__ const*,int,int) ; 
 int /*<<< orphan*/  qr_line_fit_points (int /*<<< orphan*/ ,int**,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  qr_line_orient (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void qr_line_fit_finder_pair(qr_line _l,const qr_aff *_aff,
 const qr_finder *_f0,const qr_finder *_f1,int _e){
  qr_point          *pts;
  int                npts;
  qr_finder_edge_pt *edge_pts;
  qr_point           q;
  int                n0;
  int                n1;
  int                i;
  n0=_f0->ninliers[_e];
  n1=_f1->ninliers[_e];
  /*We could write a custom version of qr_line_fit_points that accesses
     edge_pts directly, but this saves on code size and doesn't measurably slow
     things down.*/
  npts=QR_MAXI(n0,1)+QR_MAXI(n1,1);
  pts=(qr_point *)malloc(npts*sizeof(*pts));
  if(n0>0){
    edge_pts=_f0->edge_pts[_e];
    for(i=0;i<n0;i++){
      pts[i][0]=edge_pts[i].pos[0];
      pts[i][1]=edge_pts[i].pos[1];
    }
  }
  else{
    q[0]=_f0->o[0];
    q[1]=_f0->o[1];
    q[_e>>1]+=_f0->size[_e>>1]*(2*(_e&1)-1);
    qr_aff_project(pts[0],_aff,q[0],q[1]);
    n0++;
  }
  if(n1>0){
    edge_pts=_f1->edge_pts[_e];
    for(i=0;i<n1;i++){
      pts[n0+i][0]=edge_pts[i].pos[0];
      pts[n0+i][1]=edge_pts[i].pos[1];
    }
  }
  else{
    q[0]=_f1->o[0];
    q[1]=_f1->o[1];
    q[_e>>1]+=_f1->size[_e>>1]*(2*(_e&1)-1);
    qr_aff_project(pts[n0],_aff,q[0],q[1]);
    n1++;
  }
  qr_line_fit_points(_l,pts,npts,_aff->res);
  /*Make sure at least one finder center lies in the positive halfspace.*/
  qr_line_orient(_l,_f0->c->pos[0],_f0->c->pos[1]);
  free(pts);
}