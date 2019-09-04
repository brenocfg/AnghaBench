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
typedef  void** qr_point ;
struct TYPE_3__ {int** fwd; int res; int ires; void* y0; void* x0; void*** inv; } ;
typedef  TYPE_1__ qr_aff ;

/* Variables and functions */
 void* QR_DIVROUND (int,int) ; 
 int QR_MAXI (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  abs (int) ; 
 int qr_ilog (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void qr_aff_init(qr_aff *_aff,
 const qr_point _p0,const qr_point _p1,const qr_point _p2,int _res){
  int det;
  int ires;
  int dx1;
  int dy1;
  int dx2;
  int dy2;
  /*det is ensured to be positive by our caller.*/
  dx1=_p1[0]-_p0[0];
  dx2=_p2[0]-_p0[0];
  dy1=_p1[1]-_p0[1];
  dy2=_p2[1]-_p0[1];
  det=dx1*dy2-dy1*dx2;
  ires=QR_MAXI((qr_ilog(abs(det))>>1)-2,0);
  _aff->fwd[0][0]=dx1;
  _aff->fwd[0][1]=dx2;
  _aff->fwd[1][0]=dy1;
  _aff->fwd[1][1]=dy2;
  _aff->inv[0][0]=QR_DIVROUND(dy2<<_res,det>>ires);
  _aff->inv[0][1]=QR_DIVROUND(-dx2<<_res,det>>ires);
  _aff->inv[1][0]=QR_DIVROUND(-dy1<<_res,det>>ires);
  _aff->inv[1][1]=QR_DIVROUND(dx1<<_res,det>>ires);
  _aff->x0=_p0[0];
  _aff->y0=_p0[1];
  _aff->res=_res;
  _aff->ires=ires;
}