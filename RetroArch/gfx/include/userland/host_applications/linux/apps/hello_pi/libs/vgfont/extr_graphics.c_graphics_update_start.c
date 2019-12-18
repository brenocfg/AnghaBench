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
typedef  int int32_t ;
struct TYPE_2__ {scalar_t__ dispman_start_count; scalar_t__ current_update; } ;

/* Variables and functions */
 scalar_t__ DISPMANX_NO_HANDLE ; 
 TYPE_1__ gx ; 
 int /*<<< orphan*/  vc_assert (int /*<<< orphan*/ ) ; 
 scalar_t__ vc_dispmanx_update_start (int) ; 

int32_t graphics_update_start(void)
{
   int32_t success = 0;

   //check we are not already in an update
   if ( 0 == gx.dispman_start_count )
   {
      gx.current_update = vc_dispmanx_update_start( 10 );
      if( gx.current_update == DISPMANX_NO_HANDLE )
      {
         //error
         success = -1;
         vc_assert( 0 );
      }
   }

   if( success == 0 )
   {
      //inc the counter
      gx.dispman_start_count++;
   }

   return success;
}