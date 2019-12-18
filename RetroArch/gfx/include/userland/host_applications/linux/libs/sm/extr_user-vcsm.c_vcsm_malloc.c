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
 int /*<<< orphan*/  VCSM_CACHE_TYPE_NONE ; 
 unsigned int vcsm_malloc_cache (unsigned int,int /*<<< orphan*/ ,char*) ; 

unsigned int vcsm_malloc( unsigned int size, char *name )
{
   return vcsm_malloc_cache( size, VCSM_CACHE_TYPE_NONE, name );
}