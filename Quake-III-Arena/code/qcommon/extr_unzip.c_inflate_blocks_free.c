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
typedef  int /*<<< orphan*/  z_streamp ;
struct TYPE_5__ {struct TYPE_5__* hufts; struct TYPE_5__* window; } ;
typedef  TYPE_1__ inflate_blocks_statef ;

/* Variables and functions */
 int /*<<< orphan*/  Tracev (char*) ; 
 int /*<<< orphan*/  ZFREE (int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  Z_NULL ; 
 int Z_OK ; 
 int /*<<< orphan*/  inflate_blocks_reset (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int inflate_blocks_free(inflate_blocks_statef *s, z_streamp z)
{
  inflate_blocks_reset(s, z, Z_NULL);
  ZFREE(z, s->window);
  ZFREE(z, s->hufts);
  ZFREE(z, s);
  Tracev(("inflate:   blocks freed\n"));
  return Z_OK;
}