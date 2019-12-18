#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int n; int* trig; int scale; } ;
typedef  TYPE_1__ mdct_lookup ;
typedef  int REG_TYPE ;
typedef  int DATA_TYPE ;

/* Variables and functions */
 int MULT_NORM (int) ; 
 int* alloca (int) ; 
 int /*<<< orphan*/  mdct_bitreverse (TYPE_1__*,int*) ; 
 int /*<<< orphan*/  mdct_butterflies (TYPE_1__*,int*,int) ; 

void mdct_forward(mdct_lookup *init, DATA_TYPE *in, DATA_TYPE *out){
  int n=init->n;
  int n2=n>>1;
  int n4=n>>2;
  int n8=n>>3;
  DATA_TYPE *w=alloca(n*sizeof(*w)); /* forward needs working space */
  DATA_TYPE *w2=w+n2;

  /* rotate */

  /* window + rotate + step 1 */

  REG_TYPE r0;
  REG_TYPE r1;
  DATA_TYPE *x0=in+n2+n4;
  DATA_TYPE *x1=x0+1;
  DATA_TYPE *T=init->trig+n2;

  int i=0;

  for(i=0;i<n8;i+=2){
    x0 -=4;
    T-=2;
    r0= x0[2] + x1[0];
    r1= x0[0] + x1[2];
    w2[i]=   MULT_NORM(r1*T[1] + r0*T[0]);
    w2[i+1]= MULT_NORM(r1*T[0] - r0*T[1]);
    x1 +=4;
  }

  x1=in+1;

  for(;i<n2-n8;i+=2){
    T-=2;
    x0 -=4;
    r0= x0[2] - x1[0];
    r1= x0[0] - x1[2];
    w2[i]=   MULT_NORM(r1*T[1] + r0*T[0]);
    w2[i+1]= MULT_NORM(r1*T[0] - r0*T[1]);
    x1 +=4;
  }

  x0=in+n;

  for(;i<n2;i+=2){
    T-=2;
    x0 -=4;
    r0= -x0[2] - x1[0];
    r1= -x0[0] - x1[2];
    w2[i]=   MULT_NORM(r1*T[1] + r0*T[0]);
    w2[i+1]= MULT_NORM(r1*T[0] - r0*T[1]);
    x1 +=4;
  }


  mdct_butterflies(init,w+n2,n2);
  mdct_bitreverse(init,w);

  /* roatate + window */

  T=init->trig+n2;
  x0=out+n2;

  for(i=0;i<n4;i++){
    x0--;
    out[i] =MULT_NORM((w[0]*T[0]+w[1]*T[1])*init->scale);
    x0[0]  =MULT_NORM((w[0]*T[1]-w[1]*T[0])*init->scale);
    w+=2;
    T+=2;
  }
}