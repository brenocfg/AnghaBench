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
typedef  int* qr_line ;
struct TYPE_3__ {int** fwd; } ;
typedef  TYPE_1__ qr_aff ;

/* Variables and functions */
 int QR_DIVROUND (int,int) ; 
 scalar_t__ QR_INT_BITS ; 
 int QR_MAXI (int /*<<< orphan*/ ,scalar_t__) ; 
 int abs (int) ; 
 scalar_t__ qr_ilog (int) ; 

__attribute__((used)) static int qr_aff_line_step(const qr_aff *_aff,qr_line _l,
 int _v,int _du,int *_dv){
  int shift;
  int round;
  int dv;
  int n;
  int d;
  n=_aff->fwd[0][_v]*_l[0]+_aff->fwd[1][_v]*_l[1];
  d=_aff->fwd[0][1-_v]*_l[0]+_aff->fwd[1][1-_v]*_l[1];
  if(d<0){
    n=-n;
    d=-d;
  }
  shift=QR_MAXI(0,qr_ilog(_du)+qr_ilog(abs(n))+3-QR_INT_BITS);
  round=(1<<shift)>>1;
  n=n+round>>shift;
  d=d+round>>shift;
  /*The line should not be outside 45 degrees of horizontal/vertical.
    TODO: We impose this restriction to help ensure the loop below terminates,
     but it should not technically be required.
    It also, however, ensures we avoid division by zero.*/
  if(abs(n)>=d)return -1;
  n=-_du*n;
  dv=QR_DIVROUND(n,d);
  if(abs(dv)>=_du)return -1;
  *_dv=dv;
  return 0;
}