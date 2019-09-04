#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/ * qr_point ;
typedef  int /*<<< orphan*/  qr_line ;
struct TYPE_6__ {int /*<<< orphan*/ * pos; } ;
typedef  TYPE_2__ qr_finder_edge_pt ;
struct TYPE_7__ {int* ninliers; TYPE_1__* c; TYPE_2__** edge_pts; } ;
typedef  TYPE_3__ qr_finder ;
struct TYPE_5__ {int /*<<< orphan*/ * pos; } ;

/* Variables and functions */
 int /*<<< orphan*/  free (int /*<<< orphan*/ **) ; 
 scalar_t__ malloc (int) ; 
 int /*<<< orphan*/  qr_line_fit_points (int /*<<< orphan*/ ,int /*<<< orphan*/ **,int,int) ; 
 int /*<<< orphan*/  qr_line_orient (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int qr_line_fit_finder_edge(qr_line _l,
 const qr_finder *_f,int _e,int _res){
  qr_finder_edge_pt *edge_pts;
  qr_point          *pts;
  int                npts;
  int                i;
  npts=_f->ninliers[_e];
  if(npts<2)return -1;
  /*We could write a custom version of qr_line_fit_points that accesses
     edge_pts directly, but this saves on code size and doesn't measurably slow
     things down.*/
  pts=(qr_point *)malloc(npts*sizeof(*pts));
  edge_pts=_f->edge_pts[_e];
  for(i=0;i<npts;i++){
    pts[i][0]=edge_pts[i].pos[0];
    pts[i][1]=edge_pts[i].pos[1];
  }
  qr_line_fit_points(_l,pts,npts,_res);
  /*Make sure the center of the finder pattern lies in the positive halfspace
     of the line.*/
  qr_line_orient(_l,_f->c->pos[0],_f->c->pos[1]);
  free(pts);
  return 0;
}