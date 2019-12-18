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
typedef  int /*<<< orphan*/  tmp_exec ;

/* Variables and functions */
 int /*<<< orphan*/  environ ; 
 int /*<<< orphan*/  execve (char const*,char* const*,int /*<<< orphan*/ ) ; 
 char* getenv (char*) ; 
 int /*<<< orphan*/  memcpy (char*,char*,size_t) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,char*,char const*) ; 
 char* strchr (char*,char) ; 
 size_t strlen (char*) ; 

int execvp( const char* filename, char* const argv[] ) {
    char* path;
    char* separator;
    char tmp_path[ 128 ];
    char tmp_exec[ 128 ];

    execve( filename, argv, environ );

    path = getenv( "PATH" );

    if ( path == NULL ) {
        return -1;
    }

    do {
        separator = strchr( path, ':' );

        if ( separator == NULL ) {
            memcpy( tmp_path, path, strlen( path ) + 1 );
        } else {
            size_t length = ( separator - path );

            memcpy( tmp_path, path, length );
            tmp_path[ length ] = 0;
        }

        snprintf( tmp_exec, sizeof( tmp_exec ), "%s/%s", tmp_path, filename );
        execve( tmp_exec, argv, environ );

        path = separator + 1;
    } while ( separator != NULL );

    return -1;
}