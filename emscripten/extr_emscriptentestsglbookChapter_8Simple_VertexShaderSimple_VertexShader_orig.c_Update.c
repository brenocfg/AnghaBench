#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {float angle; int /*<<< orphan*/  mvpMatrix; } ;
typedef  TYPE_1__ UserData ;
struct TYPE_5__ {scalar_t__ height; scalar_t__ width; scalar_t__ userData; } ;
typedef  float GLfloat ;
typedef  int /*<<< orphan*/  ESMatrix ;
typedef  TYPE_2__ ESContext ;

/* Variables and functions */
 int /*<<< orphan*/  esMatrixLoadIdentity (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  esMatrixMultiply (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  esPerspective (int /*<<< orphan*/ *,float,float,float,float) ; 
 int /*<<< orphan*/  esRotate (int /*<<< orphan*/ *,float,double,double,double) ; 
 int /*<<< orphan*/  esTranslate (int /*<<< orphan*/ *,double,double,double) ; 

void Update ( ESContext *esContext, float deltaTime )
{
   UserData *userData = (UserData*) esContext->userData;
   ESMatrix perspective;
   ESMatrix modelview;
   float    aspect;
   
   // Compute a rotation angle based on time to rotate the cube
   userData->angle += ( deltaTime * 40.0f );
   if( userData->angle >= 360.0f )
      userData->angle -= 360.0f;

   // Compute the window aspect ratio
   aspect = (GLfloat) esContext->width / (GLfloat) esContext->height;
   
   // Generate a perspective matrix with a 60 degree FOV
   esMatrixLoadIdentity( &perspective );
   esPerspective( &perspective, 60.0f, aspect, 1.0f, 20.0f );

   // Generate a model view matrix to rotate/translate the cube
   esMatrixLoadIdentity( &modelview );

   // Translate away from the viewer
   esTranslate( &modelview, 0.0, 0.0, -2.0 );

   // Rotate the cube
   esRotate( &modelview, userData->angle, 1.0, 0.0, 1.0 );
   
   // Compute the final MVP by multiplying the 
   // modevleiw and perspective matrices together
   esMatrixMultiply( &userData->mvpMatrix, &modelview, &perspective );
}