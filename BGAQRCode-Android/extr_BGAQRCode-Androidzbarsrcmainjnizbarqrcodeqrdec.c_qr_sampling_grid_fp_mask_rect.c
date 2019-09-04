#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int* fpmask; } ;
typedef  TYPE_1__ qr_sampling_grid ;

/* Variables and functions */
 int QR_INT_BITS ; 
 int QR_INT_LOGBITS ; 

__attribute__((used)) static void qr_sampling_grid_fp_mask_rect(qr_sampling_grid *_grid,int _dim,
 int _u,int _v,int _w,int _h){
  int i;
  int j;
  int stride;
  stride=_dim+QR_INT_BITS-1>>QR_INT_LOGBITS;
  /*Note that we store bits column-wise, since that's how they're read out of
     the grid.*/
  for(j=_u;j<_u+_w;j++)for(i=_v;i<_v+_h;i++){
    _grid->fpmask[j*stride+(i>>QR_INT_LOGBITS)]|=1<<(i&QR_INT_BITS-1);
  }
}