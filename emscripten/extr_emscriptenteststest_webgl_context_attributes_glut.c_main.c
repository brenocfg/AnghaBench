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
 unsigned int GLUT_DOUBLE ; 
 unsigned int GLUT_RGBA ; 
 int /*<<< orphan*/  REPORT_RESULT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WINDOWS_SIZE ; 
 int /*<<< orphan*/  checkContextAttributesSupport () ; 
 int /*<<< orphan*/  draw () ; 
 int /*<<< orphan*/  glewInit () ; 
 int /*<<< orphan*/  glutCreateWindow (char*) ; 
 int /*<<< orphan*/  glutDisplayFunc (int /*<<< orphan*/  (*) ()) ; 
 int /*<<< orphan*/  glutInit (int*,char**) ; 
 int /*<<< orphan*/  glutInitDisplayMode (unsigned int) ; 
 int /*<<< orphan*/  glutInitWindowSize (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  initGlObjects () ; 
 int /*<<< orphan*/  result ; 

int main(int argc, char *argv[]) {
    
    checkContextAttributesSupport(); 
    
    unsigned int glutDisplayMode = GLUT_RGBA | GLUT_DOUBLE;
        
#ifdef AA_ACTIVATED
    antiAliasingActivated = true;
    glutDisplayMode |= GLUT_MULTISAMPLE;
#endif
    
#ifdef DEPTH_ACTIVATED
    depthActivated = true;
    glutDisplayMode |= GLUT_DEPTH;
#endif
    
#ifdef STENCIL_ACTIVATED
    stencilActivated = true;
    glutDisplayMode |= GLUT_STENCIL;
#endif
    
#ifdef ALPHA_ACTIVATED
    alphaActivated = true;
    glutDisplayMode |= GLUT_ALPHA;
#endif
    
    glutInit(&argc, argv);
    glutInitWindowSize(WINDOWS_SIZE, WINDOWS_SIZE);
    glutInitDisplayMode(glutDisplayMode);
    glutCreateWindow("WebGL");
    glutDisplayFunc(draw);  
     
    glewInit();
    initGlObjects();
    
    draw();
    
    REPORT_RESULT(result);
    
    return 0;
}