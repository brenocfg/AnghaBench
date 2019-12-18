#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_1__* z_streamp ;
struct TYPE_8__ {struct TYPE_8__* state; struct TYPE_8__* blocks; struct TYPE_8__* zfree; } ;

/* Variables and functions */
 int /*<<< orphan*/  Tracev (char*) ; 
 int /*<<< orphan*/  ZFREE (TYPE_1__*,TYPE_1__*) ; 
 TYPE_1__* Z_NULL ; 
 int Z_OK ; 
 int Z_STREAM_ERROR ; 
 int /*<<< orphan*/  inflate_blocks_free (TYPE_1__*,TYPE_1__*) ; 

int inflateEnd(z_streamp z)
{
  if (z == Z_NULL || z->state == Z_NULL || z->zfree == Z_NULL)
    return Z_STREAM_ERROR;
  if (z->state->blocks != Z_NULL)
    inflate_blocks_free(z->state->blocks, z);
  ZFREE(z, z->state);
  z->state = Z_NULL;
  Tracev(("inflate: end\n"));
  return Z_OK;
}