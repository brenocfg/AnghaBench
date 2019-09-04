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

__attribute__((used)) static int qr_sampling_grid_is_in_fp(const qr_sampling_grid *_grid,int _dim,
 int _u,int _v){
  return _grid->fpmask[_u*(_dim+QR_INT_BITS-1>>QR_INT_LOGBITS)
   +(_v>>QR_INT_LOGBITS)]>>(_v&QR_INT_BITS-1)&1;
}