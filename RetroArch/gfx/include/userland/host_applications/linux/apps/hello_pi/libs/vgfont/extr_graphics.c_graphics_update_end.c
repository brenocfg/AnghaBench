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
struct TYPE_2__ {scalar_t__ current_update; scalar_t__ dispman_start_count; } ;

/* Variables and functions */
 scalar_t__ DISPMANX_NO_HANDLE ; 
 int /*<<< orphan*/  eglWaitClient () ; 
 TYPE_1__ gx ; 
 int /*<<< orphan*/  vc_assert (int /*<<< orphan*/ ) ; 
 scalar_t__ vc_dispmanx_update_submit_sync (scalar_t__) ; 
 scalar_t__ vcos_verify (int) ; 

int32_t graphics_update_end( void )
{
   int32_t success = -1;

   // make sure you are checking the return value of graphics_update_start
   if(vcos_verify(gx.current_update != DISPMANX_NO_HANDLE))
   {
      //check we are in an update
      if(vcos_verify(gx.dispman_start_count > 0))
      {
         //dec the counter
         gx.dispman_start_count--;

         success = 0;

         //is the counter now 0?
         if( 0 == gx.dispman_start_count )
         {
            eglWaitClient();
            if( vc_dispmanx_update_submit_sync( gx.current_update ) != 0 )
            {
               //error
               success = -1;
               vc_assert( 0 );
            }
         }
      }
   }

   return success;
}