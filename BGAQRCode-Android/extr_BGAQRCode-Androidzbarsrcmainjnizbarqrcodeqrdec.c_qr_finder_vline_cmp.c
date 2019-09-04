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
struct TYPE_2__ {scalar_t__* pos; } ;
typedef  TYPE_1__ qr_finder_line ;

/* Variables and functions */

__attribute__((used)) static int qr_finder_vline_cmp(const void *_a,const void *_b){
  const qr_finder_line *a;
  const qr_finder_line *b;
  a=(const qr_finder_line *)_a;
  b=(const qr_finder_line *)_b;
  return ((a->pos[0]>b->pos[0])-(a->pos[0]<b->pos[0])<<1)+
   (a->pos[1]>b->pos[1])-(a->pos[1]<b->pos[1]);
}