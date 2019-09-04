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
typedef  int /*<<< orphan*/  ESContext ;

/* Variables and functions */
 int /*<<< orphan*/  ShutDown (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  exit (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  printf (char*) ; 

void Key ( ESContext *esContext, unsigned char key, int x, int y)
{
   switch ( key )
   {
   case 'm':
      printf( "Saw an 'm'\n" );
      break;

   case 'a':
      printf( "Saw an 'a'\n" );
      break;

   case '1':
      printf( "Saw a '1'\n" );
      break;

   case 033: // ASCII Escape Key
	   ShutDown( esContext );
	   exit( 0 );
	   break;
   }
}