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
typedef  int /*<<< orphan*/  TestStatus ;
typedef  int /*<<< orphan*/  SDL_Surface ;
typedef  int /*<<< orphan*/  GLuint ;
typedef  scalar_t__ GLenum ;

/* Variables and functions */
 int /*<<< orphan*/  GL_LINEAR ; 
 scalar_t__ GL_NO_ERROR ; 
 int GL_RGBA ; 
 int /*<<< orphan*/  GL_TEXTURE_2D ; 
 int /*<<< orphan*/  GL_TEXTURE_MAG_FILTER ; 
 int /*<<< orphan*/  GL_TEXTURE_MIN_FILTER ; 
 int GL_UNSIGNED_BYTE ; 
 int /*<<< orphan*/  SDL_GL_DOUBLEBUFFER ; 
 int /*<<< orphan*/  SDL_GL_SetAttribute (int /*<<< orphan*/ ,int) ; 
 char* SDL_GetError () ; 
 int /*<<< orphan*/  SDL_INIT_VIDEO ; 
 scalar_t__ SDL_Init (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SDL_OPENGL ; 
 int /*<<< orphan*/  SDL_Quit () ; 
 int /*<<< orphan*/ * SDL_SetVideoMode (int,int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TEST_STATUS_FAILURE ; 
 int /*<<< orphan*/  TEST_STATUS_SUCCESS ; 
 int /*<<< orphan*/  clear_gl_errors () ; 
 int /*<<< orphan*/  exit_with_status (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free (void*) ; 
 int /*<<< orphan*/  glBindTexture (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  glDeleteTextures (int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  glGenTextures (int,int /*<<< orphan*/ *) ; 
 scalar_t__ glGetError () ; 
 int /*<<< orphan*/  glTexImage2D (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int,int,int /*<<< orphan*/ ,int,int,void*) ; 
 int /*<<< orphan*/  glTexParameteri (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 void* malloc (int) ; 
 int /*<<< orphan*/  printf (char*,...) ; 

int main(int argc, char *argv[])
{
    TestStatus passed = TEST_STATUS_SUCCESS;
    SDL_Surface *screen;

    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
        printf("SDL_Init failed with %s\n", SDL_GetError());
        exit_with_status(TEST_STATUS_FAILURE);
    }

    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
    screen = SDL_SetVideoMode(640, 480, 16, SDL_OPENGL);
    if (!screen) {
        printf("SDL_SetVideoMode failed with %s\n", SDL_GetError());
        exit_with_status(TEST_STATUS_FAILURE);
    }

    GLuint texture;
    glGenTextures(1, &texture);

    glBindTexture(GL_TEXTURE_2D, texture);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    // Allocate space for a 32x32 image with 4 bytes per pixel.
    // No need to fill it with any useful information, as these tests are
    // only designed to make sure glTexImage2D doesn't crash on unsupported
    // formats.
    void* pixels = malloc(4 * 32 * 32);
    if (pixels == NULL) {
        printf("Unable to allocate pixel data\n");
        exit_with_status(TEST_STATUS_FAILURE);
    }

    // First, try 0xffff for the internal format - should fail
    glTexImage2D(GL_TEXTURE_2D, 0, 0xffff, 32, 32, 0, GL_RGBA, GL_UNSIGNED_BYTE, pixels);
    GLenum err = glGetError();
    if (err == GL_NO_ERROR) {
        printf("internal format == 0xffff succeeded, but should have failed\n");
        passed = TEST_STATUS_FAILURE;
    }
    clear_gl_errors();

    // Try 0xffff for the format - should fail
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, 32, 32, 0, 0xffff, GL_UNSIGNED_BYTE, pixels);
    err = glGetError();
    if (err == GL_NO_ERROR) {
        printf("format == 0xffff succeeded, but should have failed\n");
        passed = TEST_STATUS_FAILURE;
    }
    clear_gl_errors();

    // Try 0xffff for the type - should fail
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, 32, 32, 0, GL_RGBA, 0xffff, pixels);
    err = glGetError();
    if (err == GL_NO_ERROR) {
        printf("type == 0xffff succeeded, but should have failed\n");
        passed = TEST_STATUS_FAILURE;
    }
    clear_gl_errors();

    // Try GL_RGBA/GL_UNSIGNED_BYTE - should succeed
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, 32, 32, 0, GL_RGBA, GL_UNSIGNED_BYTE, pixels);
    err = glGetError();
    if (err != GL_NO_ERROR) {
        printf("GL_RGBA/GL_UNSIGNED_BYTE failed with %x, but should have succeeded\n", err);
        passed = TEST_STATUS_FAILURE;
    }
    clear_gl_errors();

    // Clean up objects
    glBindTexture(GL_TEXTURE_2D, 0);
    glDeleteTextures(1, &texture);
    free(pixels);

    // 'screen' is freed implicitly by SDL_Quit()
    SDL_Quit();

    exit_with_status(passed);
}