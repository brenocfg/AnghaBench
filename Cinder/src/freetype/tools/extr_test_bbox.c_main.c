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
 int /*<<< orphan*/  REPEAT ; 
 int /*<<< orphan*/  dummy_outline_1 ; 
 int /*<<< orphan*/  dummy_outline_2 ; 
 int /*<<< orphan*/  dummy_outline_3 ; 
 int /*<<< orphan*/  printf (char*) ; 
 int /*<<< orphan*/  profile_outline (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

int  main( int  argc, char**  argv )
  {
    printf( "outline #1\n" );
    profile_outline( &dummy_outline_1, REPEAT );

    printf( "outline #2\n" );
    profile_outline( &dummy_outline_2, REPEAT );

    printf( "outline #3\n" );
    profile_outline( &dummy_outline_3, REPEAT );

    return 0;
  }