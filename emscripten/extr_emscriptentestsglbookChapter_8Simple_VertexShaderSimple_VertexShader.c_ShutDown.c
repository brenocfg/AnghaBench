#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/  programObject; struct TYPE_5__* indices; struct TYPE_5__* vertices; } ;
typedef  TYPE_1__ UserData ;
struct TYPE_6__ {TYPE_1__* userData; } ;
typedef  TYPE_2__ ESContext ;

/* Variables and functions */
 int /*<<< orphan*/  free (TYPE_1__*) ; 
 int /*<<< orphan*/  glDeleteProgram (int /*<<< orphan*/ ) ; 

void ShutDown ( ESContext *esContext )
{
   UserData *userData = esContext->userData;

   if ( userData->vertices != NULL )
   {
      free ( userData->vertices );
   }

   if ( userData->indices != NULL )
   {
      free ( userData->indices );
   }

   // Delete program object
   glDeleteProgram ( userData->programObject );

   free(userData);
}