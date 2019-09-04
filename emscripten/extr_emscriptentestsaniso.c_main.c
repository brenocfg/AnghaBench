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
typedef  int /*<<< orphan*/  SDL_Surface ;
typedef  int /*<<< orphan*/  GLuint ;
typedef  int GLint ;
typedef  double GLfloat ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int /*<<< orphan*/  GL_COLOR_BUFFER_BIT ; 
 int /*<<< orphan*/  GL_COMPRESSED_RGBA_S3TC_DXT5_EXT ; 
 int /*<<< orphan*/  GL_DEPTH_ATTACHMENT ; 
 int /*<<< orphan*/  GL_EXTENSIONS ; 
 int /*<<< orphan*/  GL_FRAMEBUFFER ; 
 int /*<<< orphan*/  GL_FRAMEBUFFER_ATTACHMENT_OBJECT_TYPE ; 
 int GL_LINEAR ; 
 int /*<<< orphan*/  GL_MAX_TEXTURE_MAX_ANISOTROPY_EXT ; 
 int /*<<< orphan*/  GL_MODELVIEW ; 
 int /*<<< orphan*/  GL_PROJECTION ; 
 int /*<<< orphan*/  GL_RENDERBUFFER ; 
 int /*<<< orphan*/  GL_TEXTURE_2D ; 
 int /*<<< orphan*/  GL_TEXTURE_MAG_FILTER ; 
 int /*<<< orphan*/  GL_TEXTURE_MAX_ANISOTROPY_EXT ; 
 int /*<<< orphan*/  GL_TEXTURE_MIN_FILTER ; 
 int /*<<< orphan*/  GL_TRIANGLES ; 
 int /*<<< orphan*/  GL_TRIANGLE_STRIP ; 
 int /*<<< orphan*/  GL_VENDOR ; 
 int MAX (int,int) ; 
 int /*<<< orphan*/  SDL_Delay (int) ; 
 int /*<<< orphan*/  SDL_GL_DOUBLEBUFFER ; 
 int /*<<< orphan*/  SDL_GL_SetAttribute (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  SDL_GL_SwapBuffers () ; 
 char* SDL_GetError () ; 
 int /*<<< orphan*/  SDL_INIT_VIDEO ; 
 scalar_t__ SDL_Init (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SDL_OPENGL ; 
 int /*<<< orphan*/  SDL_Quit () ; 
 int /*<<< orphan*/ * SDL_SetVideoMode (int,int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  fclose (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * fopen (char*,char*) ; 
 int const fread (char*,int,int const,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  glBegin (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  glBindFramebuffer (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  glBindTexture (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  glClear (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  glClearColor (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  glCompressedTexImage2D (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ ,int,char*) ; 
 int /*<<< orphan*/  glDeleteTextures (int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  glEnable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  glEnd () ; 
 int /*<<< orphan*/  glGenTextures (int,int /*<<< orphan*/ *) ; 
 int glGetError () ; 
 int /*<<< orphan*/  glGetFramebufferAttachmentParameteriv (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  glGetIntegerv (int /*<<< orphan*/ ,int*) ; 
 scalar_t__ glGetString (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  glLoadIdentity () ; 
 int /*<<< orphan*/  glLoadMatrixf (double*) ; 
 int /*<<< orphan*/  glMatrixMode (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  glTexCoord2i (int,int) ; 
 int /*<<< orphan*/  glTexParameteri (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 void glVertex2i (int,int) ; 
 void glVertex3f (int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  glViewport (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int) ; 
 int hasext (char const*,char*) ; 
 scalar_t__ malloc (int const) ; 
 int /*<<< orphan*/  printf (char*,...) ; 

int main(int argc, char *argv[])
{
    SDL_Surface *screen;

    // Slightly different SDL initialization
    if ( SDL_Init(SDL_INIT_VIDEO) != 0 ) {
        printf("Unable to initialize SDL: %s\n", SDL_GetError());
        return 1;
    }

    SDL_GL_SetAttribute( SDL_GL_DOUBLEBUFFER, 1 ); // *new*

    screen = SDL_SetVideoMode( 600, 600, 16, SDL_OPENGL ); // *changed*
    if ( !screen ) {
        printf("Unable to set video mode: %s\n", SDL_GetError());
        return 1;
    }

    // Check extensions

    const char *exts = (const char *)glGetString(GL_EXTENSIONS);
    assert(hasext(exts, "GL_EXT_texture_filter_anisotropic"));

    const char *vendor = (const char *)glGetString(GL_VENDOR);
    printf("vendor: %s\n", vendor);

    GLint aniso;
    glGetIntegerv(GL_MAX_TEXTURE_MAX_ANISOTROPY_EXT, &aniso);
    printf("Max anisotropy: %d (using that)\n", aniso);
    assert(aniso >= 4);

    // Set the OpenGL state after creating the context with SDL_SetVideoMode

    glClearColor( 0, 0, 0, 0 );

    glEnable( GL_TEXTURE_2D ); // Needed when we're using the fixed-function pipeline.

    glViewport( 0, 0, 600, 600 );

    glMatrixMode( GL_PROJECTION );
    GLfloat matrixData[] = { 2.0/600,        0,        0,  0,
                                   0, -2.0/600,        0,  0,
                                   0,        0, -2.0/600,  0,
                                  -1,        1,        0,  1 };
    glLoadMatrixf(matrixData); // test loadmatrix

    glMatrixMode( GL_MODELVIEW );
    glLoadIdentity();


    // Load the OpenGL texture

    GLuint texture, texture2;

    const int DDS_SIZE = 43920;
    FILE *dds = fopen("water.dds", "rb");
    assert(dds);
    char *ddsdata = (char*)malloc(DDS_SIZE);
    assert(fread(ddsdata, 1, DDS_SIZE, dds) == DDS_SIZE);
    fclose(dds);

    {
      glGenTextures( 1, &texture );
      glBindTexture( GL_TEXTURE_2D, texture );

      char *curr = ddsdata + 128;
      int level = 0;
      int w = 512;
      int h = 64;
      while (level < 5) {
        printf("uploading level %d: %d, %d\n", level, w, h);
        assert(!glGetError());
        glCompressedTexImage2D(GL_TEXTURE_2D, level, GL_COMPRESSED_RGBA_S3TC_DXT5_EXT, w, h, 0, w*h, curr);
        assert(!glGetError());
        curr += MAX(w, 4)*MAX(h, 4);
        w /= 2;
        h /= 2;
        level++;
      }
      glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR );
      glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR );
    }
    {
      glGenTextures( 1, &texture2 );
      glBindTexture( GL_TEXTURE_2D, texture2 );

      char *curr = ddsdata + 128;
      int level = 0;
      int w = 512;
      int h = 64;
      while (level < 5) {
        printf("uploading level %d: %d, %d\n", level, w, h);
        assert(!glGetError());
        glCompressedTexImage2D(GL_TEXTURE_2D, level, GL_COMPRESSED_RGBA_S3TC_DXT5_EXT, w, h, 0, w*h, curr);
        assert(!glGetError());
        curr += MAX(w, 4)*MAX(h, 4);
        w /= 2;
        h /= 2;
        level++;
      }
      glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR );
      glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR );
      glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MAX_ANISOTROPY_EXT, aniso);
    }
    {
      assert(!glGetError());
      glBindFramebuffer(GL_RENDERBUFFER, 0);
      assert(glGetError());

      GLint out = 321;
      assert(!glGetError());
      glGetFramebufferAttachmentParameteriv(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_FRAMEBUFFER_ATTACHMENT_OBJECT_TYPE, &out); // invalid, just test output
      assert(out == 0);
    }

    // Prepare and Render

    // Clear the screen before drawing
    glClear( GL_COLOR_BUFFER_BIT );

    // Bind the texture to which subsequent calls refer to
    int w = 10;
    int n = 15;
    glBindTexture( GL_TEXTURE_2D, texture );
    for (int x = 0; x < n; x++) {
      int start = x*w*2;
      glBegin( GL_TRIANGLES );
        glTexCoord2i( 1, 0 ); glVertex2i( start  ,   0 );
        glTexCoord2i( 0, 0 ); glVertex3f( start+w, 300, 0 );
        glTexCoord2i( 1, 1 ); glVertex3f( start-w, 300, 0 );
      glEnd();
    }
    glBindTexture( GL_TEXTURE_2D, texture2 );
    for (int x = 0; x < n; x++) {
      int start = n*w*2 + x*w*2;
      glBegin( GL_TRIANGLES );
        glTexCoord2i( 1, 0 ); glVertex3f( start  ,   0, 0 );
        glTexCoord2i( 0, 0 ); glVertex3f( start+w, 300, 0 );
        glTexCoord2i( 1, 1 ); glVertex3f( start-w, 300, 0 );
      glEnd();
    }
/*
    int w = 8;
    int n = 20;
    for (int x = 0; x < n; x++) {
      for (int y = 0; y < n*2; y++) {
        glBindTexture( GL_TEXTURE_2D, texture );
        glBegin( GL_TRIANGLE_STRIP );
          glTexCoord2i( 0, 0 ); glVertex3f( x*w,           y*(w), 0 );
          glTexCoord2i( 1, 0 ); glVertex3f( (x+1)*(w-2*y/n),     y*(w), 0 );
          glTexCoord2i( 1, 1 ); glVertex3f( (x+1)*(w-2*y/n), (y+1)*(w), 0 );
          glTexCoord2i( 0, 1 ); glVertex3f( x*w,       (y+1)*(w), 0 );
        glEnd();
        glBindTexture( GL_TEXTURE_2D, texture2 );
        glBegin( GL_TRIANGLE_STRIP );
          glTexCoord2i( 0, 0 ); glVertex3f( n*w + x*w,           y*(w), 0 );
          glTexCoord2i( 1, 0 ); glVertex3f( n*w + (x+1)*(w-2*y/n),     y*(w), 0 );
          glTexCoord2i( 1, 1 ); glVertex3f( n*w + (x+1)*(w-2*y/n), (y+1)*(w), 0 );
          glTexCoord2i( 0, 1 ); glVertex3f( n*w + x*w,       (y+1)*(w), 0 );
        glEnd();
      }
    }
*/
    SDL_GL_SwapBuffers();

#ifndef __EMSCRIPTEN__
    // Wait for 3 seconds to give us a chance to see the image
    SDL_Delay(2000);
#endif

    // Now we can delete the OpenGL texture and close down SDL
    glDeleteTextures( 1, &texture );

    SDL_Quit();

    // check for asm compilation bug with aliased functions with different sigs

    glBegin( GL_TRIANGLE_STRIP );
    void (*f)(int, int) = glVertex2i;
    if ((int)f % 16 == 4) f(5, 7);
    void (*g)(int, int) = glVertex3f;
    if ((int)g % 16 == 4) g(5, 7);
    return (int)f + (int)g;
}