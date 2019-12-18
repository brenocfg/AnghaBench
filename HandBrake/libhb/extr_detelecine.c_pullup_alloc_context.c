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
struct pullup_context {int dummy; } ;

/* Variables and functions */
 struct pullup_context* calloc (int,int) ; 

struct pullup_context * pullup_alloc_context( void )
{
    struct pullup_context * c;

    c = calloc( 1, sizeof(struct pullup_context)) ;

    return c;
}