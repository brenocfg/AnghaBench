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
typedef  int /*<<< orphan*/  response ;
typedef  scalar_t__ VCHIQ_INSTANCE_T ;

/* Variables and functions */
 scalar_t__ VCHIQ_SUCCESS ; 
 int /*<<< orphan*/  exit (int) ; 
 int /*<<< orphan*/  global_connection ; 
 scalar_t__ global_initialise_instance ; 
 int /*<<< orphan*/  printf (char*) ; 
 int /*<<< orphan*/  single_get_func_table () ; 
 int vc_gencmd (char*,int,char*) ; 
 int /*<<< orphan*/  vc_vchi_cec_init (scalar_t__,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  vc_vchi_dispmanx_init (scalar_t__,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  vc_vchi_gencmd_init (scalar_t__,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  vc_vchi_tv_init (scalar_t__,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  vchi_connect (int /*<<< orphan*/ *,int,scalar_t__) ; 
 int /*<<< orphan*/  vchi_create_connection (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int vchi_initialise (scalar_t__*) ; 
 int /*<<< orphan*/  vchi_mphi_message_driver_func_table () ; 
 scalar_t__ vchiq_initialise (scalar_t__*) ; 
 int /*<<< orphan*/  vcos_assert (int) ; 
 int /*<<< orphan*/  vcos_init () ; 
 int /*<<< orphan*/  vcos_log (char*) ; 

void bcm_host_init(void)
{
   VCHIQ_INSTANCE_T vchiq_instance;
   static int initted;
   int success = -1;
   char response[ 128 ];

   if (initted)
	return;
   initted = 1;
   vcos_init();

   if (vchiq_initialise(&vchiq_instance) != VCHIQ_SUCCESS)
   {
      printf("* failed to open vchiq instance\n");
      exit(-1);
   }

   vcos_log("vchi_initialise");
   success = vchi_initialise( &global_initialise_instance);
   vcos_assert(success == 0);
   vchiq_instance = (VCHIQ_INSTANCE_T)global_initialise_instance;

   global_connection = vchi_create_connection(single_get_func_table(),
                                              vchi_mphi_message_driver_func_table());

   vcos_log("vchi_connect");
   vchi_connect(&global_connection, 1, global_initialise_instance);

   vc_vchi_gencmd_init (global_initialise_instance, &global_connection, 1);
   vc_vchi_dispmanx_init (global_initialise_instance, &global_connection, 1);
   vc_vchi_tv_init (global_initialise_instance, &global_connection, 1);
   vc_vchi_cec_init (global_initialise_instance, &global_connection, 1);
   //vc_vchi_bufman_init (global_initialise_instance, &global_connection, 1);

   if ( success == 0 )
   {
      success = vc_gencmd( response, sizeof(response), "set_vll_dir /sd/vlls" );
      vcos_assert( success == 0 );
   }
}