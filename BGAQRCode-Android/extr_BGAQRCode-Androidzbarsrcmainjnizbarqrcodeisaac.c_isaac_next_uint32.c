#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {size_t n; int* r; } ;
typedef  TYPE_1__ isaac_ctx ;

/* Variables and functions */
 int /*<<< orphan*/  isaac_update (TYPE_1__*) ; 

unsigned isaac_next_uint32(isaac_ctx *_ctx){
  if(!_ctx->n)isaac_update(_ctx);
  return _ctx->r[--_ctx->n];
}