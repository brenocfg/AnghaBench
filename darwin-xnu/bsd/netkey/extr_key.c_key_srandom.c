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
struct timeval {int /*<<< orphan*/  tv_usec; } ;

/* Variables and functions */
 int /*<<< orphan*/  microtime (struct timeval*) ; 
 int /*<<< orphan*/  random () ; 
 int /*<<< orphan*/  srandom (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
key_srandom(void)
{
#ifdef __APPLE__
	/* Our PRNG is based on Yarrow and doesn't need to be seeded */
	random();
#else
	struct timeval tv;
	
	microtime(&tv);
	
	srandom(tv.tv_usec);
#endif
	
	return;
}