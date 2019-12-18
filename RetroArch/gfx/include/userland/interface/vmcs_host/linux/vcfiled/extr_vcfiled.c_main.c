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
typedef  int /*<<< orphan*/  lockfile ;
typedef  scalar_t__ VCHIQ_INSTANCE_T ;

/* Variables and functions */
 int /*<<< orphan*/  INT_MAX ; 
 int /*<<< orphan*/  LOG_ERR ; 
 int /*<<< orphan*/  LOG_INFO ; 
 int /*<<< orphan*/  VCFILED_LOCKFILE ; 
 scalar_t__ VCHIQ_SUCCESS ; 
 scalar_t__ daemon (int /*<<< orphan*/ ,int) ; 
 int errno ; 
 int /*<<< orphan*/  foreground ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  global_connection ; 
 scalar_t__ global_initialise_instance ; 
 int /*<<< orphan*/  lock_prefix ; 
 scalar_t__ lock_prefix_set ; 
 scalar_t__ log_stderr ; 
 int /*<<< orphan*/  logmsg (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  parse_args (int,char* const*) ; 
 char const* progname ; 
 int /*<<< orphan*/  single_get_func_table () ; 
 int /*<<< orphan*/  sleep (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stderr ; 
 char* strrchr (char const*,char) ; 
 int /*<<< orphan*/  vc_vchi_filesys_init (scalar_t__,int /*<<< orphan*/ *,int) ; 
 int vcfiled_lock (char*,int /*<<< orphan*/  (*) (int /*<<< orphan*/ ,char*,char* const)) ; 
 int /*<<< orphan*/  vchi_connect (int /*<<< orphan*/ *,int,scalar_t__) ; 
 int /*<<< orphan*/  vchi_create_connection (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int vchi_initialise (scalar_t__*) ; 
 int /*<<< orphan*/  vchi_mphi_message_driver_func_table () ; 
 scalar_t__ vchiq_initialise (scalar_t__*) ; 
 int /*<<< orphan*/  vcos_assert (int) ; 
 int /*<<< orphan*/  vcos_deinit () ; 
 int /*<<< orphan*/  vcos_init () ; 
 int /*<<< orphan*/  vcos_safe_sprintf (char*,int,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,...) ; 

int main(int argc, char *const *argv)
{
   VCHIQ_INSTANCE_T vchiq_instance;
   int success;
   char lockfile[128];

   progname = argv[0];
   const char *sep = strrchr(progname, '/');
   if (sep)
      progname = sep+1;

   parse_args(argc, argv);

   if (!foreground)
   {
      if ( daemon( 0, 1 ) != 0 )
      {
         fprintf( stderr, "Failed to daemonize: errno = %d", errno );
         return -1;
      }
      log_stderr = 0;
   }
   if ( lock_prefix_set )
   {
      vcos_safe_sprintf( lockfile, sizeof(lockfile), 0, "%s/%s", lock_prefix, VCFILED_LOCKFILE );
   }
   else
   {
      vcos_safe_sprintf( lockfile, sizeof(lockfile), 0, "%s", VCFILED_LOCKFILE );
   }
   success = vcfiled_lock(lockfile, logmsg);
   if (success != 0)
   {
      return -1;
   }

   logmsg( LOG_INFO, "vcfiled started" );

   vcos_init();

   if (vchiq_initialise(&vchiq_instance) != VCHIQ_SUCCESS)
   {
      logmsg(LOG_ERR, "%s: failed to open vchiq instance\n", argv[0]);
      return -1;
   }

   success = vchi_initialise( &global_initialise_instance);
   vcos_assert(success == 0);
   vchiq_instance = (VCHIQ_INSTANCE_T)global_initialise_instance;

   global_connection = vchi_create_connection(single_get_func_table(),
                                              vchi_mphi_message_driver_func_table());

   vchi_connect(&global_connection, 1, global_initialise_instance);

   vc_vchi_filesys_init (global_initialise_instance, &global_connection, 1);

   for (;;)
   {
      sleep(INT_MAX);
   }

   vcos_deinit ();

   return 0;
}