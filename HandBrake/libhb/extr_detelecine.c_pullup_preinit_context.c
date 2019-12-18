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
struct pullup_context {int /*<<< orphan*/  nplanes; void* background; void* stride; void* h; void* w; void* bpp; } ;

/* Variables and functions */
 void* calloc (int /*<<< orphan*/ ,int) ; 

void pullup_preinit_context( struct pullup_context * c )
{
    c->bpp        = calloc( c->nplanes, sizeof(int) );
    c->w          = calloc( c->nplanes, sizeof(int) );
    c->h          = calloc( c->nplanes, sizeof(int) );
    c->stride     = calloc( c->nplanes, sizeof(int) );
    c->background = calloc( c->nplanes, sizeof(int) );
}