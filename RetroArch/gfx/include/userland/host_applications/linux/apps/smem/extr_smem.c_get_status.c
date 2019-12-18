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
typedef  int VCSM_STATUS_T ;

/* Variables and functions */
#define  VCSM_STATUS_HOST_WALK_MAP 131 
#define  VCSM_STATUS_HOST_WALK_PID_ALLOC 130 
 int const VCSM_STATUS_HOST_WALK_PID_MAP ; 
#define  VCSM_STATUS_VC_MAP_ALL 129 
#define  VCSM_STATUS_VC_WALK_ALLOC 128 
 int /*<<< orphan*/  vcsm_status (int const,int) ; 

__attribute__((used)) static int get_status( VCSM_STATUS_T mode, int pid )
{
   switch ( mode )
   {
      case VCSM_STATUS_VC_WALK_ALLOC:
         vcsm_status( VCSM_STATUS_VC_WALK_ALLOC, -1 );
      break;

      case VCSM_STATUS_HOST_WALK_MAP:
         if ( pid != -1 )
         {
            vcsm_status( VCSM_STATUS_HOST_WALK_PID_MAP, pid );
         }
         else
         {
            vcsm_status( VCSM_STATUS_HOST_WALK_MAP, -1 );
         }
      break;

      case VCSM_STATUS_HOST_WALK_PID_ALLOC:
         vcsm_status( VCSM_STATUS_HOST_WALK_PID_ALLOC, pid );
      break;

      case VCSM_STATUS_VC_MAP_ALL:
         vcsm_status( VCSM_STATUS_VC_WALK_ALLOC, -1 );
         vcsm_status( VCSM_STATUS_HOST_WALK_MAP, -1 );
      break;

      default:
      break;
   }

   return 0;
}