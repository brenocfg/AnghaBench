#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int /*<<< orphan*/ * CurrentWindow; } ;

/* Variables and functions */
 int /*<<< orphan*/  FREEGLUT_INTERNAL_ERROR_EXIT_IF_NOT_INITIALISED (char*) ; 
 int GLUT_FULLY_COVERED ; 
 int GLUT_HIDDEN ; 
 int GLUT_NOT_VISIBLE ; 
 int GLUT_VISIBLE ; 
 int /*<<< orphan*/  INVOKE_WCB (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  Visibility ; 
 TYPE_1__ fgStructure ; 
 int /*<<< orphan*/  freeglut_return_if_fail (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void fghVisibility( int status )
{
    int glut_status = GLUT_VISIBLE;

    FREEGLUT_INTERNAL_ERROR_EXIT_IF_NOT_INITIALISED ( "Visibility Callback" );
    freeglut_return_if_fail( fgStructure.CurrentWindow );

    if( ( GLUT_HIDDEN == status )  || ( GLUT_FULLY_COVERED == status ) )
        glut_status = GLUT_NOT_VISIBLE;
    INVOKE_WCB( *( fgStructure.CurrentWindow ), Visibility, ( glut_status ) );
}