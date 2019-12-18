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
typedef  enum gfx_ctx_api { ____Placeholder_gfx_ctx_api } gfx_ctx_api ;

/* Variables and functions */
 scalar_t__ EGL_FALSE ; 
 int /*<<< orphan*/  EGL_OPENGL_ES_API ; 
 int GFX_CTX_OPENGL_ES_API ; 
 int ctx_orbis_api ; 
 scalar_t__ eglBindAPI (int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool orbis_ctx_bind_api(void *data,
                                enum gfx_ctx_api api, unsigned major, unsigned minor)
{
    (void)data;
    ctx_orbis_api = api;

    if (api == GFX_CTX_OPENGL_ES_API)
        if (eglBindAPI(EGL_OPENGL_ES_API) != EGL_FALSE)
            return true;

    return false;
}