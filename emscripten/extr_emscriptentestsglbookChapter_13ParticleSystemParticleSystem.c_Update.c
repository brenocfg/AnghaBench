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
struct TYPE_4__ {float time; int /*<<< orphan*/  timeLoc; int /*<<< orphan*/  colorLoc; int /*<<< orphan*/  centerPositionLoc; } ;
typedef  TYPE_1__ UserData ;
struct TYPE_5__ {TYPE_1__* userData; } ;
typedef  TYPE_2__ ESContext ;

/* Variables and functions */
 int /*<<< orphan*/  glUniform1f (int /*<<< orphan*/ ,float) ; 
 int /*<<< orphan*/  glUniform3fv (int /*<<< orphan*/ ,int,float*) ; 
 int /*<<< orphan*/  glUniform4fv (int /*<<< orphan*/ ,int,float*) ; 
 double myrandom () ; 

void Update ( ESContext *esContext, float deltaTime )
{
//  deltaTime = 0.1;
   UserData *userData = esContext->userData;
  
   userData->time += deltaTime;

   if ( userData->time >= 1.0f )
   {
      float centerPos[3];
      float color[4];

      userData->time = 0.0f;

      // Pick a new start location and color
      centerPos[0] = myrandom() - 0.5f;
      centerPos[1] = myrandom() - 0.5f;
      centerPos[2] = myrandom() - 0.5f;
      
      glUniform3fv ( userData->centerPositionLoc, 1, &centerPos[0] );

      // Random color
      color[0] = myrandom() * 0.5 + 0.5f;
      color[1] = myrandom() * 0.5 + 0.5f;
      color[2] = myrandom() * 0.5 + 0.5f;
      color[3] = 1.0;

      glUniform4fv ( userData->colorLoc, 1, &color[0] );
   }

   // Load uniform time variable
   glUniform1f ( userData->timeLoc, userData->time );
}