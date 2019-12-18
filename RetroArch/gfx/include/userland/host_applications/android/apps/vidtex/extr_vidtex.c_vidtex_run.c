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
typedef  int /*<<< orphan*/  VIDTEX_T ;
typedef  int /*<<< orphan*/  VIDTEX_PARAMS_T ;
typedef  int /*<<< orphan*/  EGLNativeWindowType ;

/* Variables and functions */
 int /*<<< orphan*/ * vidtex_create (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vidtex_destroy (int /*<<< orphan*/ *) ; 
 int vidtex_play (int /*<<< orphan*/ *,int /*<<< orphan*/  const*) ; 

int vidtex_run(const VIDTEX_PARAMS_T *params, EGLNativeWindowType win)
{
   VIDTEX_T *vt;
   int rv = -1;

   vt = vidtex_create(win);
   if (vt)
   {
      rv = vidtex_play(vt, params);
      vidtex_destroy(vt);
   }

   return rv;
}