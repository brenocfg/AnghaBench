#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {scalar_t__ boffs; scalar_t__ eoffs; scalar_t__ len; int /*<<< orphan*/ * pos; } ;
typedef  TYPE_1__ qr_finder_line ;
struct TYPE_7__ {int /*<<< orphan*/ * pos; } ;
typedef  TYPE_2__ qr_finder_edge_pt ;
struct TYPE_8__ {int nlines; TYPE_1__** lines; } ;
typedef  TYPE_3__ qr_finder_cluster ;

/* Variables and functions */

__attribute__((used)) static int qr_finder_edge_pts_fill(qr_finder_edge_pt *_edge_pts,int _nedge_pts,
 qr_finder_cluster **_neighbors,int _nneighbors,int _v){
  int i;
  for(i=0;i<_nneighbors;i++){
    qr_finder_cluster *c;
    int                j;
    c=_neighbors[i];
    for(j=0;j<c->nlines;j++){
      qr_finder_line *l;
      l=c->lines[j];
      if(l->boffs>0){
        _edge_pts[_nedge_pts].pos[0]=l->pos[0];
        _edge_pts[_nedge_pts].pos[1]=l->pos[1];
        _edge_pts[_nedge_pts].pos[_v]-=l->boffs;
        _nedge_pts++;
      }
      if(l->eoffs>0){
        _edge_pts[_nedge_pts].pos[0]=l->pos[0];
        _edge_pts[_nedge_pts].pos[1]=l->pos[1];
        _edge_pts[_nedge_pts].pos[_v]+=l->len+l->eoffs;
        _nedge_pts++;
      }
    }
  }
  return _nedge_pts;
}