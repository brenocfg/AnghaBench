#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  UserData ;
struct TYPE_8__ {int /*<<< orphan*/ * userData; } ;
typedef  TYPE_1__ ESContext ;

/* Variables and functions */
 int /*<<< orphan*/  Draw ; 
 int ES_WINDOW_DEPTH ; 
 int ES_WINDOW_RGB ; 
 int ES_WINDOW_STENCIL ; 
 int /*<<< orphan*/  Init (TYPE_1__*) ; 
 int /*<<< orphan*/  ShutDown (TYPE_1__*) ; 
 int /*<<< orphan*/  esCreateWindow (TYPE_1__*,char*,int,int,int) ; 
 int /*<<< orphan*/  esInitContext (TYPE_1__*) ; 
 int /*<<< orphan*/  esMainLoop (TYPE_1__*) ; 
 int /*<<< orphan*/  esRegisterDrawFunc (TYPE_1__*,int /*<<< orphan*/ ) ; 

int main ( int argc, char *argv[] )
{
   ESContext esContext;
   UserData  userData;

   esInitContext ( &esContext );
   esContext.userData = &userData;

   esCreateWindow ( &esContext, "Stencil Test", 320, 240,
                    ES_WINDOW_RGB | ES_WINDOW_DEPTH | ES_WINDOW_STENCIL );
   
   if ( !Init ( &esContext ) )
      return 0;

   esRegisterDrawFunc ( &esContext, Draw );
   
   esMainLoop ( &esContext );

   ShutDown ( &esContext );
}