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
typedef  int uint32_t ;
typedef  void* int32_t ;
typedef  int /*<<< orphan*/  VCSM_STATUS_T ;
struct TYPE_5__ {scalar_t__ want_prefix; } ;
struct TYPE_6__ {TYPE_1__ flags; } ;

/* Variables and functions */
 int OPTSTRING_LEN ; 
#define  OPT_ALLOC 131 
#define  OPT_HELP 130 
#define  OPT_PID 129 
#define  OPT_STATUS 128 
 int /*<<< orphan*/  VCOS_LOG_INFO ; 
 int /*<<< orphan*/  VCSM_STATUS_HOST_WALK_MAP ; 
 int /*<<< orphan*/  VCSM_STATUS_HOST_WALK_PID_ALLOC ; 
 int /*<<< orphan*/  VCSM_STATUS_NONE ; 
 int /*<<< orphan*/  VCSM_STATUS_VC_MAP_ALL ; 
 int /*<<< orphan*/  VCSM_STATUS_VC_WALK_ALLOC ; 
 int /*<<< orphan*/  blah_blah ; 
 int /*<<< orphan*/  create_optstring (char*) ; 
 int /*<<< orphan*/  exit (int) ; 
 int /*<<< orphan*/  get_status (int /*<<< orphan*/ ,int) ; 
 int getopt_long_only (int,char**,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  long_opts ; 
 int /*<<< orphan*/  memcpy (void*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  memset (void*,int /*<<< orphan*/ ,int) ; 
 char* optarg ; 
 int optind ; 
 int /*<<< orphan*/  quit_event ; 
 int /*<<< orphan*/  show_usage () ; 
 TYPE_2__ smem_log_category ; 
 int sscanf (char*,char*,char*) ; 
 int /*<<< orphan*/  start_monitor () ; 
 scalar_t__ strtol (char*,char**,int) ; 
 int /*<<< orphan*/  strtoul (char*,char**,int) ; 
 int /*<<< orphan*/  vcos_event_delete (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vcos_event_wait (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vcos_init () ; 
 int /*<<< orphan*/  vcos_log_info (char*,...) ; 
 int /*<<< orphan*/  vcos_log_register (char*,TYPE_2__*) ; 
 int /*<<< orphan*/  vcos_log_set_level (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vcos_strcasecmp (char*,char*) ; 
 int /*<<< orphan*/  vcsm_exit () ; 
 int /*<<< orphan*/  vcsm_free (unsigned int) ; 
 int vcsm_init () ; 
 void* vcsm_lock (unsigned int) ; 
 unsigned int vcsm_malloc (int,char*) ; 
 void* vcsm_resize (unsigned int,int) ; 
 void* vcsm_unlock_hdl (unsigned int) ; 
 void* vcsm_unlock_ptr (void*) ; 
 void* vcsm_usr_handle (void*) ; 
 int /*<<< orphan*/  vcsm_vc_hdl_from_hdl (unsigned int) ; 
 void* vcsm_vc_hdl_from_ptr (void*) ; 

int main( int argc, char **argv )
{
   int32_t ret;
   char optstring[OPTSTRING_LEN];
   int  opt;
   int  opt_alloc = 0;
   int  opt_status = 0;
   uint32_t alloc_size = 0;
   int  opt_pid = -1;
   VCSM_STATUS_T status_mode = VCSM_STATUS_NONE;

   void *usr_ptr_1;
   unsigned int usr_hdl_1;
#if defined(DOUBLE_ALLOC) || defined(RESIZE_ALLOC)
   void *usr_ptr_2;
   unsigned int usr_hdl_2;
#endif

   // Initialize VCOS
   vcos_init();

   vcos_log_set_level(&smem_log_category, VCOS_LOG_INFO);
   smem_log_category.flags.want_prefix = 0;
   vcos_log_register( "smem", &smem_log_category );

   // Create the option string that we will be using to parse the arguments
   create_optstring( optstring );

   // Parse the command line arguments
   while (( opt = getopt_long_only( argc, argv, optstring, long_opts,
                                    NULL )) != -1 )
   {
      switch ( opt )
      {
         case 0:
         {
            // getopt_long returns 0 for entries where flag is non-NULL
            break;
         }
         case OPT_ALLOC:
         {
            char *end;
            alloc_size = (uint32_t)strtoul( optarg, &end, 10 );
            if (end == optarg)
            {
               vcos_log_info( "Invalid arguments '%s'", optarg );
               goto err_out;
            }

            opt_alloc = 1;
            break;
         }
         case OPT_PID:
         {
            char *end;
            opt_pid = (int)strtol( optarg, &end, 10 );
            if (end == optarg)
            {
               vcos_log_info( "Invalid arguments '%s'", optarg );
               goto err_out;
            }

            break;
         }
         case OPT_STATUS:
         {
            char status_str[32];

            /* coverity[secure_coding] String length specified, so can't overflow */
            if ( sscanf( optarg, "%31s", status_str ) != 1 )
            {
               vcos_log_info( "Invalid arguments '%s'", optarg );
               goto err_out;
            }

            if ( vcos_strcasecmp( status_str, "all" ) == 0 )
            {
               status_mode = VCSM_STATUS_VC_MAP_ALL;
            }
            else if ( vcos_strcasecmp( status_str, "vc" ) == 0 )
            {
               status_mode = VCSM_STATUS_VC_WALK_ALLOC;
            }
            else if ( vcos_strcasecmp( status_str, "map" ) == 0 )
            {
               status_mode = VCSM_STATUS_HOST_WALK_MAP;
            }
            else if ( vcos_strcasecmp( status_str, "host" ) == 0 )
            {
               status_mode = VCSM_STATUS_HOST_WALK_PID_ALLOC;
            }
            else
            {
               goto err_out;
            }

            opt_status = 1;
            break;
         }
         default:
         {
            vcos_log_info( "Unrecognized option '%d'", opt );
            goto err_usage;
         }
         case '?':
         case OPT_HELP:
         {
            goto err_usage;
         }
      } // end switch
   } // end while

   argc -= optind;
   argv += optind;

   if (( optind == 1 ) || ( argc > 0 ))
   {
      if ( argc > 0 )
      {
         vcos_log_info( "Unrecognized argument -- '%s'", *argv );
      }

      goto err_usage;
   }

   // Start the shared memory support.
   if ( vcsm_init() == -1 )
   {
      vcos_log_info( "Cannot initialize smem device" );
      goto err_out;
   }

   if ( opt_alloc == 1 )
   {
      vcos_log_info( "Allocating 2 times %u-bytes in shared memory", alloc_size );

      usr_hdl_1 = vcsm_malloc( alloc_size,
                               "smem-test-alloc" );

      vcos_log_info( "Allocation 1 result: user %x, vc-hdl %x",
                     usr_hdl_1, vcsm_vc_hdl_from_hdl( usr_hdl_1 ) );

#if defined(DOUBLE_ALLOC) || defined(RESIZE_ALLOC)
      usr_hdl_2 = vcsm_malloc( alloc_size,
                               NULL );
      vcos_log_info( "Allocation 2 result: user %x",
                     usr_hdl_2 );

      usr_ptr_2 = vcsm_lock( usr_hdl_2 );
      vcos_log_info( "Allocation 2 : lock %p",
                     usr_ptr_2 );
      vcos_log_info( "Allocation 2 : unlock %d",
                     vcsm_unlock_hdl( usr_hdl_2 ) );
#endif

      // Do a simple write/read test.
      if ( usr_hdl_1 != 0 )
      {
         usr_ptr_1 = vcsm_lock( usr_hdl_1 );
         vcos_log_info( "Allocation 1 : lock %p",
                        usr_ptr_1 );
         if ( usr_ptr_1 )
         {
            memset ( usr_ptr_1,
                     0,
                     alloc_size );
            memcpy ( usr_ptr_1,
                     blah_blah,
                     32 );
            vcos_log_info( "Allocation 1 contains: \"%s\"",
                           (char *)usr_ptr_1 );

            vcos_log_info( "Allocation 1: vc-hdl %x",
                           vcsm_vc_hdl_from_ptr ( usr_ptr_1 ) );
            vcos_log_info( "Allocation 1: usr-hdl %x",
                           vcsm_usr_handle ( usr_ptr_1 ) );
            vcos_log_info( "Allocation 1 : unlock %d",
                           vcsm_unlock_ptr( usr_ptr_1 ) );
         }

         usr_ptr_1 = vcsm_lock( usr_hdl_1 );
         vcos_log_info( "Allocation 1 (relock) : lock %p",
                        usr_ptr_1 );
         if ( usr_ptr_1 )
         {
            vcos_log_info( "Allocation 1 (relock) : unlock %d",
                           vcsm_unlock_hdl( usr_hdl_1 ) );
         }
      }

#if defined(RESIZE_ALLOC)
      ret = vcsm_resize( usr_hdl_1, 2 * alloc_size );
      vcos_log_info( "Allocation 1 : resize %d", ret );
      if ( ret == 0 )
      {
         usr_ptr_1 = vcsm_lock( usr_hdl_1 );
         vcos_log_info( "Allocation 1 (resize) : lock %p",
                        usr_ptr_1 );
         if ( usr_ptr_1 )
         {
            memset ( usr_ptr_1,
                     0,
                     2 * alloc_size );
            memcpy ( usr_ptr_1,
                     blah_blah,
                     32 );
            vcos_log_info( "Allocation 1 (resized) contains: \"%s\"",
                           (char *)usr_ptr_1 );
            vcos_log_info( "Allocation 1 (resized) : unlock %d",
                           vcsm_unlock_ptr( usr_ptr_1 ) );
         }
      }

      // This checks that the memory can be remapped properly
      // because the Block 1 expanded beyond Block 2 boundary.
      //
      usr_ptr_2 = vcsm_lock( usr_hdl_2 );
      vcos_log_info( "Allocation 2 : lock %p",
                     usr_ptr_2 );
      vcos_log_info( "Allocation 2 : unlock %d",
                     vcsm_unlock_hdl( usr_hdl_2 ) );

      // This checks that we can free a memory block even if it
      // is locked, which could be the case if the application
      // dies.
      //
      usr_ptr_2 = vcsm_lock( usr_hdl_2 );
      vcos_log_info( "Allocation 2 : lock %p",
                     usr_ptr_2 );
      vcsm_free ( usr_hdl_2 );
#endif

#if defined(DOUBLE_ALLOC)
#endif
   }

   if ( opt_status == 1 )
   {
      get_status( status_mode, opt_pid );
   }

   // If we allocated something, wait for the signal to exit to give chance for the
   // user to poke around the allocation test.
   //
   if ( opt_alloc == 1 )
   {
      start_monitor();

      vcos_event_wait( &quit_event );
      vcos_event_delete( &quit_event );
   }

   // Terminate the shared memory support.
   vcsm_exit ();
   goto err_out;

err_usage:
   show_usage();

err_out:
   exit( 1 );
}