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
struct TYPE_3__ {scalar_t__ cmap; scalar_t__ wnd; int /*<<< orphan*/ * ctx; int /*<<< orphan*/ * vi; int /*<<< orphan*/ * dpy; } ;
typedef  TYPE_1__ GLContext ;

/* Variables and functions */

void InitContext (GLContext* ctx)
{
  ctx->dpy = NULL;
  ctx->vi = NULL;
  ctx->ctx = NULL;
  ctx->wnd = 0;
  ctx->cmap = 0;
}