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
struct TYPE_3__ {scalar_t__ bufend; scalar_t__ bufbeg; scalar_t__ pos; } ;
typedef  TYPE_1__ mime_encoder_state ;

/* Variables and functions */

__attribute__((used)) static void cleanup_encoder_state(mime_encoder_state *p)
{
  p->pos = 0;
  p->bufbeg = 0;
  p->bufend = 0;
}