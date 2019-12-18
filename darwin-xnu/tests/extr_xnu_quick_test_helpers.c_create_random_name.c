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
struct stat {int dummy; } ;

/* Variables and functions */
 scalar_t__ EEXIST ; 
 scalar_t__ ENOENT ; 
 int O_CREAT ; 
 int O_EXCL ; 
 int O_RDWR ; 
 scalar_t__ PATH_MAX ; 
 int S_IRGRP ; 
 int S_IROTH ; 
 int S_IRUSR ; 
 int S_IWUSR ; 
 int /*<<< orphan*/  T_ASSERT_LT_ULONG (scalar_t__,unsigned long,char*) ; 
 int /*<<< orphan*/  T_EXPECT_TRUE (int,char*,...) ; 
 int /*<<< orphan*/  close (int) ; 
 scalar_t__ errno ; 
 int open (char*,int,int) ; 
 int rand () ; 
 int /*<<< orphan*/  sprintf (char*,char*,int) ; 
 int stat (char*,struct stat*) ; 
 int /*<<< orphan*/  strcat (char*,char*) ; 
 scalar_t__ strlen (char*) ; 
 char* strrchr (char*,char) ; 

int create_random_name( char *the_pathp, int do_open ) {
    int     i, my_err;
    int     my_fd = -1;
    
    for ( i = 0; i < 1; i++ ) {
        int         my_rand;
        char        *myp;
        char        my_name[32];
        
        my_rand = rand( );
        sprintf( &my_name[0], "%d", my_rand );
        T_ASSERT_LT_ULONG((strlen( &my_name[0] ) + strlen( the_pathp ) + 2), (unsigned long)PATH_MAX,
            "check if path to test file is less than PATH_MAX");

        // append generated file name onto our path
        myp = strrchr( the_pathp, '/' );
        *(myp + 1) = 0x00;
        strcat( the_pathp, &my_name[0] );
        if ( do_open ) {
            /* create a file with this name */
            my_fd = open( the_pathp, (O_RDWR | O_CREAT | O_EXCL),
                            (S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH) );
            T_EXPECT_TRUE((my_fd != -1 || errno == EEXIST), "open file with name %s", the_pathp);
            
            if( errno == EEXIST )
                continue;
        }
        else {
            /* make sure the name is unique */
            struct stat     my_sb;
            my_err = stat( the_pathp, &my_sb );
            T_EXPECT_TRUE((my_err == 0 || errno == ENOENT), "make sure the name is unique");
            
            if(errno == ENOENT) break;
            /* name already exists, try another */
            i--;
            continue;
        }
    }
    
    if ( my_fd != -1 )
        close( my_fd );

    if(do_open && my_fd == -1)
        return 1;

    return 0;
}