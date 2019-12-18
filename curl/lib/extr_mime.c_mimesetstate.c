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
struct TYPE_3__ {int state; scalar_t__ offset; void* ptr; } ;
typedef  TYPE_1__ mime_state ;
typedef  enum mimestate { ____Placeholder_mimestate } mimestate ;

/* Variables and functions */

__attribute__((used)) static void mimesetstate(mime_state *state, enum mimestate tok, void *ptr)
{
  state->state = tok;
  state->ptr = ptr;
  state->offset = 0;
}