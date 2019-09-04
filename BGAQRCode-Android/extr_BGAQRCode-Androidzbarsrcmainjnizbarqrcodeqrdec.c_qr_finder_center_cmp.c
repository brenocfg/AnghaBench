#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {scalar_t__ nedge_pts; scalar_t__* pos; } ;
typedef  TYPE_1__ qr_finder_center ;

/* Variables and functions */

__attribute__((used)) static int qr_finder_center_cmp(const void *_a,const void *_b){
  const qr_finder_center *a;
  const qr_finder_center *b;
  a=(const qr_finder_center *)_a;
  b=(const qr_finder_center *)_b;
  return ((b->nedge_pts>a->nedge_pts)-(b->nedge_pts<a->nedge_pts)<<2)+
   ((a->pos[1]>b->pos[1])-(a->pos[1]<b->pos[1])<<1)+
   (a->pos[0]>b->pos[0])-(a->pos[0]<b->pos[0]);
}