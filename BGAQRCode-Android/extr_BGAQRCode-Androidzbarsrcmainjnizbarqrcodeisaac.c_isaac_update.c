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
struct TYPE_3__ {unsigned int* m; unsigned int* r; unsigned int a; unsigned int b; unsigned int c; int n; } ;
typedef  TYPE_1__ isaac_ctx ;

/* Variables and functions */
 unsigned int ISAAC_MASK ; 
 int ISAAC_SZ ; 
 int ISAAC_SZ_LOG ; 

__attribute__((used)) static void isaac_update(isaac_ctx *_ctx){
  unsigned *m;
  unsigned *r;
  unsigned  a;
  unsigned  b;
  unsigned  x;
  unsigned  y;
  int       i;
  m=_ctx->m;
  r=_ctx->r;
  a=_ctx->a;
  b=_ctx->b+(++_ctx->c)&ISAAC_MASK;
  for(i=0;i<ISAAC_SZ/2;i++){
    x=m[i];
    a=(a^a<<13)+m[i+ISAAC_SZ/2]&ISAAC_MASK;
    m[i]=y=m[(x&ISAAC_SZ-1<<2)>>2]+a+b&ISAAC_MASK;
    r[i]=b=m[y>>ISAAC_SZ_LOG+2&ISAAC_SZ-1]+x&ISAAC_MASK;
    x=m[++i];
    a=(a^a>>6)+m[i+ISAAC_SZ/2]&ISAAC_MASK;
    m[i]=y=m[(x&ISAAC_SZ-1<<2)>>2]+a+b&ISAAC_MASK;
    r[i]=b=m[y>>ISAAC_SZ_LOG+2&ISAAC_SZ-1]+x&ISAAC_MASK;
    x=m[++i];
    a=(a^a<<2)+m[i+ISAAC_SZ/2]&ISAAC_MASK;
    m[i]=y=m[(x&ISAAC_SZ-1<<2)>>2]+a+b&ISAAC_MASK;
    r[i]=b=m[y>>ISAAC_SZ_LOG+2&ISAAC_SZ-1]+x&ISAAC_MASK;
    x=m[++i];
    a=(a^a>>16)+m[i+ISAAC_SZ/2]&ISAAC_MASK;
    m[i]=y=m[(x&ISAAC_SZ-1<<2)>>2]+a+b&ISAAC_MASK;
    r[i]=b=m[y>>ISAAC_SZ_LOG+2&ISAAC_SZ-1]+x&ISAAC_MASK;
  }
  for(i=ISAAC_SZ/2;i<ISAAC_SZ;i++){
    x=m[i];
    a=(a^a<<13)+m[i-ISAAC_SZ/2]&ISAAC_MASK;
    m[i]=y=m[(x&ISAAC_SZ-1<<2)>>2]+a+b&ISAAC_MASK;
    r[i]=b=m[y>>ISAAC_SZ_LOG+2&ISAAC_SZ-1]+x&ISAAC_MASK;
    x=m[++i];
    a=(a^a>>6)+m[i-ISAAC_SZ/2]&ISAAC_MASK;
    m[i]=y=m[(x&ISAAC_SZ-1<<2)>>2]+a+b&ISAAC_MASK;
    r[i]=b=m[y>>ISAAC_SZ_LOG+2&ISAAC_SZ-1]+x&ISAAC_MASK;
    x=m[++i];
    a=(a^a<<2)+m[i-ISAAC_SZ/2]&ISAAC_MASK;
    m[i]=y=m[(x&ISAAC_SZ-1<<2)>>2]+a+b&ISAAC_MASK;
    r[i]=b=m[y>>ISAAC_SZ_LOG+2&ISAAC_SZ-1]+x&ISAAC_MASK;
    x=m[++i];
    a=(a^a>>16)+m[i-ISAAC_SZ/2]&ISAAC_MASK;
    m[i]=y=m[(x&ISAAC_SZ-1<<2)>>2]+a+b&ISAAC_MASK;
    r[i]=b=m[y>>ISAAC_SZ_LOG+2&ISAAC_SZ-1]+x&ISAAC_MASK;
  }
  _ctx->b=b;
  _ctx->a=a;
  _ctx->n=ISAAC_SZ;
}