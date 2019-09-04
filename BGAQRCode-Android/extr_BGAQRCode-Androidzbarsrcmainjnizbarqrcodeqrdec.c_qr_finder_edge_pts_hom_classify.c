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
typedef  scalar_t__* qr_point ;
typedef  int /*<<< orphan*/  qr_hom ;
struct TYPE_5__ {int nedge_pts; TYPE_3__* edge_pts; } ;
typedef  TYPE_1__ qr_finder_center ;
struct TYPE_6__ {int* nedge_pts; TYPE_3__** edge_pts; int /*<<< orphan*/ * o; TYPE_1__* c; } ;
typedef  TYPE_2__ qr_finder ;
struct TYPE_7__ {int edge; scalar_t__ extent; int /*<<< orphan*/ * pos; } ;

/* Variables and functions */
 scalar_t__ abs (scalar_t__) ; 
 int /*<<< orphan*/  qr_cmp_edge_pt ; 
 scalar_t__ qr_hom_unproject (scalar_t__*,int /*<<< orphan*/  const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  qr_point_translate (scalar_t__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  qsort (TYPE_3__*,int,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void qr_finder_edge_pts_hom_classify(qr_finder *_f,const qr_hom *_hom){
  qr_finder_center *c;
  int               i;
  int               e;
  c=_f->c;
  for(e=0;e<4;e++)_f->nedge_pts[e]=0;
  for(i=0;i<c->nedge_pts;i++){
    qr_point q;
    int      d;
    if(qr_hom_unproject(q,_hom,
     c->edge_pts[i].pos[0],c->edge_pts[i].pos[1])>=0){
      qr_point_translate(q,-_f->o[0],-_f->o[1]);
      d=abs(q[1])>abs(q[0]);
      e=d<<1|(q[d]>=0);
      _f->nedge_pts[e]++;
      c->edge_pts[i].edge=e;
      c->edge_pts[i].extent=q[d];
    }
    else{
      c->edge_pts[i].edge=4;
      c->edge_pts[i].extent=q[0];
    }
  }
  qsort(c->edge_pts,c->nedge_pts,sizeof(*c->edge_pts),qr_cmp_edge_pt);
  _f->edge_pts[0]=c->edge_pts;
  for(e=1;e<4;e++)_f->edge_pts[e]=_f->edge_pts[e-1]+_f->nedge_pts[e-1];
}