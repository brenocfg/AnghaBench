#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct sockaddr_in {int /*<<< orphan*/  sin_addr; int /*<<< orphan*/  sin_port; int /*<<< orphan*/  sin_family; } ;
struct sockaddr {int dummy; } ;
struct hostent {int /*<<< orphan*/  h_addrtype; int /*<<< orphan*/  h_length; int /*<<< orphan*/  h_addr; } ;
struct TYPE_5__ {int /*<<< orphan*/  socket; } ;
typedef  TYPE_1__ hb_net_t ;
typedef  int /*<<< orphan*/  WSADATA ;

/* Variables and functions */
 int /*<<< orphan*/  MAKEWORD (int,int) ; 
 int /*<<< orphan*/  SOCK_STREAM ; 
 int WSAStartup (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 TYPE_1__* calloc (int,int) ; 
 scalar_t__ connect (int /*<<< orphan*/ ,struct sockaddr*,int) ; 
 int /*<<< orphan*/  free (TYPE_1__*) ; 
 struct hostent* gethostbyname (char*) ; 
 int /*<<< orphan*/  hb_log (char*,...) ; 
 int /*<<< orphan*/  htons (int) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (struct sockaddr_in*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  socket (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

hb_net_t * hb_net_open( char * address, int port )
{
    hb_net_t * n = calloc( sizeof( hb_net_t ), 1 );

    struct sockaddr_in   sock;
    struct hostent     * host;

#ifdef SYS_MINGW
    WSADATA wsaData;
    int iResult, winsock_init = 0;

    // Initialize Winsock
    if (!winsock_init)
    {
        iResult = WSAStartup(MAKEWORD(2, 2), &wsaData);
        if (iResult != 0)
        {
            hb_log("WSAStartup failed: %d", iResult);
            free(n);
            return NULL;
        }
        winsock_init = 1;
    }
#endif

    /* TODO: find out why this doesn't work on Win32 */
    if( !( host = gethostbyname( address ) ) )
    {
        hb_log( "gethostbyname failed (%s)", address );
        free( n );
        return NULL;
    }

    memset( &sock, 0, sizeof( struct sockaddr_in ) );
    sock.sin_family = host->h_addrtype;
    sock.sin_port   = htons( port );
    memcpy( &sock.sin_addr, host->h_addr, host->h_length );

    if( ( n->socket = socket( host->h_addrtype, SOCK_STREAM, 0 ) ) < 0 )
    {
        hb_log( "socket failed" );
        free( n );
        return NULL;
    }

    if( connect( n->socket, (struct sockaddr *) &sock,
                 sizeof( struct sockaddr_in ) ) < 0 )
    {
        hb_log( "connect failed" );
        free( n );
        return NULL;
    }

    return n;
}