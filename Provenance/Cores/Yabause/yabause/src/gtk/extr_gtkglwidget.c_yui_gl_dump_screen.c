#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  void* u8 ;
struct TYPE_8__ {int pixels_width; int pixels_height; int pixels_rowstride; int /*<<< orphan*/ * pixels; } ;
typedef  TYPE_2__ YuiGl ;
struct TYPE_7__ {int width; int height; } ;
struct TYPE_10__ {TYPE_1__ allocation; } ;
struct TYPE_9__ {int /*<<< orphan*/  (* GetGlSize ) (int*,int*) ;} ;
typedef  int /*<<< orphan*/  GLubyte ;

/* Variables and functions */
 int /*<<< orphan*/  GL_RGB ; 
 int /*<<< orphan*/  GL_UNSIGNED_BYTE ; 
 TYPE_5__* GTK_WIDGET (TYPE_2__*) ; 
 TYPE_4__* VIDCore ; 
 scalar_t__ dispbuffer ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  glReadPixels (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 void* malloc (int) ; 
 int /*<<< orphan*/  stub1 (int*,int*) ; 

void yui_gl_dump_screen(YuiGl * glxarea) {
#ifdef HAVE_LIBGTKGLEXT
	int size;

	glxarea->pixels_width = GTK_WIDGET(glxarea)->allocation.width;
	glxarea->pixels_height = GTK_WIDGET(glxarea)->allocation.height;
	glxarea->pixels_rowstride = glxarea->pixels_width * 3;
	glxarea->pixels_rowstride += (glxarea->pixels_rowstride % 4)? (4 - (glxarea->pixels_rowstride % 4)): 0;

        size = glxarea->pixels_rowstride * glxarea->pixels_height;
 
	if (glxarea->pixels) free(glxarea->pixels);
        glxarea->pixels = malloc(sizeof(GLubyte) * size);
        if (glxarea->pixels == NULL) return;    

        glReadPixels(0, 0, glxarea->pixels_width, glxarea->pixels_height, GL_RGB, GL_UNSIGNED_BYTE, glxarea->pixels);
#else
	int buf_width, buf_height;
	int i, j;
	int size;
	int cur = 0;
	u8 * pixels;
	u8 * buffer;

	VIDCore->GetGlSize( &buf_width, &buf_height );
	size = buf_width * buf_height * 3;

	glxarea->pixels_width = buf_width;
	glxarea->pixels_height = buf_height;
	glxarea->pixels_rowstride = glxarea->pixels_width * 3;
	glxarea->pixels_rowstride += (glxarea->pixels_rowstride % 4)? (4 - (glxarea->pixels_rowstride % 4)): 0;

	if (! glxarea->pixels) glxarea->pixels = malloc(sizeof(u8) * size);

	pixels = (u8 *)glxarea->pixels;
	pixels += size - (buf_width * 3);
	buffer = (u8 *)dispbuffer;

	for(i = 0;i < buf_height;i++) {
		for(j = 0;j < buf_width;j++) {
			*pixels++ = buffer[cur];
			*pixels++ = buffer[cur + 1];
			*pixels++ = buffer[cur + 2];
			cur += 4;
		}
		pixels -= buf_width * 6;
	}
#endif
}