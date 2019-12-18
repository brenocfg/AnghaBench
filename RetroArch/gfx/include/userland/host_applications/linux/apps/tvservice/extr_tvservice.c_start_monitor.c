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

/* Variables and functions */
 int /*<<< orphan*/  LOG_ERR (char*) ; 
 int /*<<< orphan*/  SIGINT ; 
 int /*<<< orphan*/  SIGTERM ; 
 scalar_t__ VCOS_SUCCESS ; 
 int /*<<< orphan*/  control_c ; 
 int /*<<< orphan*/  quit_event ; 
 int /*<<< orphan*/  signal (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tvservice_callback ; 
 int /*<<< orphan*/  vc_tv_register_callback (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ vcos_event_create (int /*<<< orphan*/ *,char*) ; 

__attribute__((used)) static int start_monitor( void )
{
   if ( vcos_event_create( &quit_event, "tvservice" ) != VCOS_SUCCESS )
   {
      LOG_ERR( "Failed to create quit event" );

      return -1;
   }

   // Handle the INT and TERM signals so we can quit
   signal( SIGINT, control_c );
   signal( SIGTERM, control_c );

   vc_tv_register_callback( &tvservice_callback, NULL );

   return 0;
}