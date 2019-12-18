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
typedef  int uint32_t ;
typedef  scalar_t__ clock_t ;
typedef  int /*<<< orphan*/  buffer ;
typedef  int /*<<< orphan*/  VCHI_INSTANCE_T ;
typedef  int /*<<< orphan*/  VCHI_CONNECTION_T ;

/* Variables and functions */
 double CLOCKS_PER_SEC ; 
 int atoi (char*) ; 
 scalar_t__ clock () ; 
 int /*<<< orphan*/  fputs (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 int /*<<< orphan*/  stdout ; 
 scalar_t__ strcmp (char*,char*) ; 
 int strlen (char*) ; 
 int vc_gencmd_read_response (char*,int) ; 
 int vc_gencmd_send (char*,char*) ; 
 int /*<<< orphan*/  vc_gencmd_stop () ; 
 int /*<<< orphan*/  vc_vchi_gencmd_init (int /*<<< orphan*/ ,int /*<<< orphan*/ **,int) ; 
 scalar_t__ vchi_connect (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ vchi_disconnect (int /*<<< orphan*/ ) ; 
 scalar_t__ vchi_initialise (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vcos_init () ; 
 size_t vcos_safe_strcpy (char*,char*,int,size_t) ; 

int main( int argc, char **argv )
{
   int instNum = 0;
   VCHI_INSTANCE_T vchi_instance;
   VCHI_CONNECTION_T *vchi_connection = NULL;

   if ( argc > 1 )
   {
       if (( strcmp( argv[1], "0" ) == 0 ) || ( strcmp( argv[1], "1" ) == 0 ))
       {
           instNum = atoi( argv[1] );
           argv++;
           argc--;
       }
   }

   vcos_init();

    if ( vchi_initialise( &vchi_instance ) != 0)
    {
        printf( "VCHI initialization failed\n" );
        return -1;
    }

    //create a vchi connection
    if ( vchi_connect( NULL, 0, vchi_instance ) != 0)
    {
        printf( "VCHI connection failed\n" );
        return -1;
    }

    vc_vchi_gencmd_init(vchi_instance, &vchi_connection, 1 );

    if (argc > 1)
    {
      int i = 1;
      char buffer[ 1024 ];
      size_t buffer_offset = 0;
      clock_t before=0, after=0;
      double time_diff;
      uint32_t show_time = 0;
      int ret;

      //reset the string
      buffer[0] = '\0';

      //first, strip out a potential leading -t
      if( strcmp( argv[1], "-t" ) == 0 )
      {
         show_time = 1;
         i++;
      }

      for (; i <= argc-1; i++)
      {
         buffer_offset = vcos_safe_strcpy( buffer, argv[i], sizeof(buffer), buffer_offset );
         buffer_offset = vcos_safe_strcpy( buffer, " ", sizeof(buffer), buffer_offset );
      }

      if( show_time )
         before = clock();

      //send the gencmd for the argument
      if (( ret = vc_gencmd_send( "%s", buffer )) != 0 )
      {
          printf( "vc_gencmd_send returned %d\n", ret );
      }

      //get + print out the response!
      if (( ret = vc_gencmd_read_response( buffer, sizeof( buffer ) )) != 0 )
      {
          printf( "vc_gencmd_read_response returned %d\n", ret );
      }

      if( show_time )
         after = clock();

      if( show_time )
      {
         time_diff = ((double) (after - before)) / CLOCKS_PER_SEC;

         printf( "Time took %f seconds (%f msecs) (%f usecs)\n", time_diff, time_diff * 1000, time_diff * 1000000 );
      }

      if ( buffer[0] != '\0' )
      {
          if ( buffer[ strlen( buffer) - 1] == '\n' )
          {
              fputs( buffer, stdout );
          }
          else
          {
              printf("%s\n", buffer );
          }
      }
    }

    vc_gencmd_stop();

    //close the vchi connection
    if ( vchi_disconnect( vchi_instance ) != 0)
    {
        printf( "VCHI disconnect failed\n" );
        return -1;
    }

   return 0;
}