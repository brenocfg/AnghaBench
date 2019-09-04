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
struct TYPE_2__ {scalar_t__ edge; scalar_t__ extent; } ;
typedef  TYPE_1__ qr_finder_edge_pt ;

/* Variables and functions */

__attribute__((used)) static int qr_cmp_edge_pt(const void *_a,const void *_b){
  const qr_finder_edge_pt *a;
  const qr_finder_edge_pt *b;
  a=(const qr_finder_edge_pt *)_a;
  b=(const qr_finder_edge_pt *)_b;
  return ((a->edge>b->edge)-(a->edge<b->edge)<<1)+
   (a->extent>b->extent)-(a->extent<b->extent);
}