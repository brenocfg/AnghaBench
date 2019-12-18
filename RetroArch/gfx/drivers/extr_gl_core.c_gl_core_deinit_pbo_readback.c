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
struct TYPE_3__ {scalar_t__* pbo_readback; int /*<<< orphan*/  pbo_readback_scaler; } ;
typedef  TYPE_1__ gl_core_t ;

/* Variables and functions */
 unsigned int GL_CORE_NUM_PBOS ; 
 int /*<<< orphan*/  glDeleteBuffers (int,scalar_t__*) ; 
 int /*<<< orphan*/  memset (scalar_t__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  scaler_ctx_gen_reset (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void gl_core_deinit_pbo_readback(gl_core_t *gl)
{
   unsigned i;
   for (i = 0; i < GL_CORE_NUM_PBOS; i++)
      if (gl->pbo_readback[i] != 0)
         glDeleteBuffers(1, &gl->pbo_readback[i]);
   memset(gl->pbo_readback, 0, sizeof(gl->pbo_readback));
   scaler_ctx_gen_reset(&gl->pbo_readback_scaler);
}