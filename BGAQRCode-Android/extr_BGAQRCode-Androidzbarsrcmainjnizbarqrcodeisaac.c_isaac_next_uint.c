#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  isaac_ctx ;

/* Variables and functions */
 unsigned int ISAAC_MASK ; 
 unsigned int isaac_next_uint32 (int /*<<< orphan*/ *) ; 

unsigned isaac_next_uint(isaac_ctx *_ctx,unsigned _n){
  unsigned r;
  unsigned v;
  unsigned d;
  do{
    r=isaac_next_uint32(_ctx);
    v=r%_n;
    d=r-v;
  }
  while((d+_n-1&ISAAC_MASK)<d);
  return v;
}