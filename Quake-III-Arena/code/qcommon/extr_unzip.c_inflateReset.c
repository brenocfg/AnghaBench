#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_1__* z_streamp ;
struct TYPE_6__ {int /*<<< orphan*/  blocks; struct TYPE_6__* state; scalar_t__ nowrap; int /*<<< orphan*/  mode; struct TYPE_6__* msg; scalar_t__ total_out; scalar_t__ total_in; } ;

/* Variables and functions */
 int /*<<< orphan*/  Tracev (char*) ; 
 TYPE_1__* Z_NULL ; 
 int Z_OK ; 
 int Z_STREAM_ERROR ; 
 int /*<<< orphan*/  imBLOCKS ; 
 int /*<<< orphan*/  imMETHOD ; 
 int /*<<< orphan*/  inflate_blocks_reset (int /*<<< orphan*/ ,TYPE_1__*,TYPE_1__*) ; 

int inflateReset(z_streamp z)
{
  if (z == Z_NULL || z->state == Z_NULL)
    return Z_STREAM_ERROR;
  z->total_in = z->total_out = 0;
  z->msg = Z_NULL;
  z->state->mode = z->state->nowrap ? imBLOCKS : imMETHOD;
  inflate_blocks_reset(z->state->blocks, z, Z_NULL);
  Tracev(("inflate: reset\n"));
  return Z_OK;
}