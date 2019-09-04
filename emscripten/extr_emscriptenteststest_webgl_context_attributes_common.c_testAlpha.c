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
 int /*<<< orphan*/  GL_COLOR_BUFFER_BIT ; 
 int /*<<< orphan*/  GL_RGBA ; 
 int /*<<< orphan*/  GL_UNSIGNED_BYTE ; 
 int WINDOWS_SIZE ; 
 float* backgroundColor ; 
 int /*<<< orphan*/  glClear (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  glClearColor (float,float,float,double) ; 
 int /*<<< orphan*/  glFinish () ; 
 int /*<<< orphan*/  glReadPixels (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned char*) ; 
 int /*<<< orphan*/  glViewport (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int) ; 

__attribute__((used)) static bool testAlpha(bool activated) {
    glViewport(0, 0, WINDOWS_SIZE, WINDOWS_SIZE);
    glClearColor(backgroundColor[0]/255.f, backgroundColor[1]/255.f, backgroundColor[2]/255.f, 0.0);
    glClear(GL_COLOR_BUFFER_BIT);
    
    bool hasAlpha = true;
    
    unsigned char buffer[(WINDOWS_SIZE*WINDOWS_SIZE)*4];
    glReadPixels(0, 0, WINDOWS_SIZE, WINDOWS_SIZE, GL_RGBA, GL_UNSIGNED_BYTE, &buffer[0]);
    glFinish();
    for (unsigned int i = 0 ; i < WINDOWS_SIZE ; ++i) {
      for (unsigned int j = 0 ; j < WINDOWS_SIZE ; ++j) {
        unsigned char r = buffer[4*(i*WINDOWS_SIZE+j)];
        unsigned char g = buffer[4*(i*WINDOWS_SIZE+j)+1];
        unsigned char b = buffer[4*(i*WINDOWS_SIZE+j)+2];
        unsigned char a = buffer[4*(i*WINDOWS_SIZE+j)+3];
        if (r == backgroundColor[0] && g == backgroundColor[1] && b == backgroundColor[2] && a == 0) {
          continue;
        } else {
          hasAlpha = false;
          break;
        }
      }
    }
    
    return (activated && hasAlpha) || (!activated && !hasAlpha);
}