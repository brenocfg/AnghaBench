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
struct TYPE_4__ {int /*<<< orphan*/  normals; int /*<<< orphan*/  vertices; int /*<<< orphan*/  programObject; int /*<<< orphan*/  textureId; } ;
typedef  TYPE_1__ UserData ;
struct TYPE_5__ {TYPE_1__* userData; } ;
typedef  TYPE_2__ ESContext ;

/* Variables and functions */
 int /*<<< orphan*/  free (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  glDeleteProgram (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  glDeleteTextures (int,int /*<<< orphan*/ *) ; 

void ShutDown ( ESContext *esContext )
{
   UserData *userData = esContext->userData;

   // Delete texture object
   glDeleteTextures ( 1, &userData->textureId );

   // Delete program object
   glDeleteProgram ( userData->programObject );

   free ( userData->vertices );
   free ( userData->normals );
	
   //free ( esContext->userData);
}