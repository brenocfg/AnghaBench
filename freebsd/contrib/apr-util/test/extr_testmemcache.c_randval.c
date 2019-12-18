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
typedef  int apr_uint32_t ;

/* Variables and functions */
 scalar_t__ RAND_MAX ; 
 int firsttime ; 
 scalar_t__ getpid () ; 
 scalar_t__ rand () ; 
 int /*<<< orphan*/  srand (unsigned int) ; 

__attribute__((used)) static int randval(apr_uint32_t high)
{
    apr_uint32_t i = 0;
    double d = 0;

    if (firsttime == 0) {
	srand((unsigned) (getpid()));
	firsttime = 1;
    }

    d = (double) rand() / ((double) RAND_MAX + 1);
    i = (int) (d * (high - 0 + 1));

    return i > 0 ? i : 1;
}