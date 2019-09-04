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
 scalar_t__ __environ_allocated ; 
 scalar_t__ environ ; 
 int /*<<< orphan*/  exit (int) ; 
 void* fdopen (int,char*) ; 
 int main (int,char**) ; 
 void* stderr ; 
 void* stdin ; 
 void* stdout ; 

void _start(int argc, char** argv) {
	stdout=fdopen(0,"rw");
	stdin=fdopen(1,"rw");
	stderr=fdopen(2,"rw");
	int error;
    environ = 0;
    __environ_allocated = 0;

    /* Call the main function of the application */

    error = main( argc, argv);

    /* Exit the process */

    exit( error );
}