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

/* Variables and functions */
 scalar_t__ GLEW_EXT_framebuffer_object ; 
 scalar_t__ GLEW_EXT_texture_filter_anisotropic ; 
 scalar_t__ GLEW_OK ; 
 int /*<<< orphan*/  SDL_INIT_VIDEO ; 
 scalar_t__ SDL_Init (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SDL_OPENGL ; 
 int /*<<< orphan*/ * SDL_SetVideoMode (int,int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/ * glewGetErrorString (int) ; 
 int glewGetExtension (char*) ; 
 int /*<<< orphan*/ * glewGetString (int) ; 
 scalar_t__ glewInit () ; 
 int glewIsSupported (char*) ; 
 int /*<<< orphan*/  strcmp (char const*,char*) ; 

int main()
{
    assert(SDL_Init(SDL_INIT_VIDEO) == 0);
    assert(SDL_SetVideoMode(640, 480, 16, SDL_OPENGL) != NULL);

    assert(glewInit() == GLEW_OK);
    assert(glewGetString(0) == NULL);
    assert(!strcmp((const char*)glewGetString(1), "1.10.0"));
    assert(!strcmp((const char*)glewGetString(2), "1"));
    assert(!strcmp((const char*)glewGetString(3), "10"));
    assert(!strcmp((const char*)glewGetString(4), "0"));

    for (int i = 0; i < 8; ++i) {
        assert(glewGetErrorString(i) != NULL);
    }

    assert(glewGetExtension("EXT_unexistant") == 0);
    assert(glewIsSupported("EXT_unexistant EXT_foobar") == 0);

    /* we can't be sure about which extension exists, so lets do test on
     * some of the common ones */
    if (GLEW_EXT_texture_filter_anisotropic) {
        assert(glewGetExtension("EXT_texture_filter_anisotropic") == 1);
        assert(glewGetExtension("GL_EXT_texture_filter_anisotropic") == 1);
    }

    if (GLEW_EXT_framebuffer_object) {
        assert(glewGetExtension("EXT_framebuffer_object") == 1);
        assert(glewGetExtension("GL_EXT_framebuffer_object") == 1);
    }

    if (GLEW_EXT_texture_filter_anisotropic &&
        GLEW_EXT_framebuffer_object) {
        assert(glewIsSupported("EXT_texture_filter_anisotropic EXT_framebuffer_object") == 1);
        assert(glewIsSupported("GL_EXT_texture_filter_anisotropic GL_EXT_framebuffer_object") == 1);
    }

#ifdef REPORT_RESULT
    REPORT_RESULT(1);
#endif
    return 0;
}