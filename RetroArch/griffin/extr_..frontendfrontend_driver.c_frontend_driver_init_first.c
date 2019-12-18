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
struct TYPE_3__ {int /*<<< orphan*/  (* init ) (void*) ;} ;
typedef  TYPE_1__ frontend_ctx_driver_t ;

/* Variables and functions */
 TYPE_1__* current_frontend_ctx ; 
 scalar_t__ frontend_ctx_init_first () ; 
 int /*<<< orphan*/  stub1 (void*) ; 

void frontend_driver_init_first(void *args)
{
   current_frontend_ctx = (frontend_ctx_driver_t*)frontend_ctx_init_first();

   if (current_frontend_ctx && current_frontend_ctx->init)
      current_frontend_ctx->init(args);
}