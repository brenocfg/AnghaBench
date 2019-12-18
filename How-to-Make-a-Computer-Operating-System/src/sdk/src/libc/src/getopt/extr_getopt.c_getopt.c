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
struct option {int dummy; } ;

/* Variables and functions */
 int _getopt_internal (int,char* const*,char const*,struct option const*,int*,int /*<<< orphan*/ ) ; 

int getopt( int argc, char* const * argv, const char* optstring ) {
    return _getopt_internal( argc,
               argv,
               optstring,
               (const struct option *) 0,
               (int *) 0,
               0 );
}