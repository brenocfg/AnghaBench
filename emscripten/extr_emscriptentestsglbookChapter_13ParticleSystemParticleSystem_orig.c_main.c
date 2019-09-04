#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  UserData ;
struct TYPE_9__ {int /*<<< orphan*/ * userData; } ;
typedef  TYPE_1__ ESContext ;

/* Variables and functions */
 int /*<<< orphan*/  Draw (TYPE_1__*) ; 
 int /*<<< orphan*/  ES_WINDOW_RGB ; 
 int /*<<< orphan*/  Init (TYPE_1__*) ; 
 int /*<<< orphan*/  ShutDown (TYPE_1__*) ; 
 int /*<<< orphan*/  esCreateWindow (TYPE_1__*,char*,int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  esInitContext (TYPE_1__*) ; 
 int /*<<< orphan*/  esRegisterDrawFunc (TYPE_1__*,int /*<<< orphan*/  (*) (TYPE_1__*)) ; 

int main ( int argc, char *argv[] )
{
   ESContext esContext;
   UserData  userData;

   esInitContext ( &esContext );
   esContext.userData = &userData;

   esCreateWindow ( &esContext, "ParticleSystem", 320, 240, ES_WINDOW_RGB );
   
   if ( !Init ( &esContext ) )
      return 0;

   esRegisterDrawFunc ( &esContext, Draw );
   //esRegisterUpdateFunc ( &esContext, Update );
   
   Draw (&esContext);
  Draw (&esContext);

   //esMainLoop ( &esContext );

   ShutDown ( &esContext );
}