#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct pullup_field {TYPE_1__* buffer; } ;
struct pullup_context {int metric_plane; int* bpp; int* stride; int metric_w; int metric_len; int metric_offset; int metric_h; } ;
struct TYPE_2__ {unsigned char** planes; } ;

/* Variables and functions */
 int /*<<< orphan*/  memset (int*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void pullup_compute_metric( struct pullup_context * c,
                                   struct pullup_field * fa, int pa,
                                   struct pullup_field * fb, int pb,
                                   int (* func)( unsigned char *,
                                                 unsigned char *, int),
                                   int * dest )
{
    unsigned char *a, *b;
    int x, y;
    int mp    = c->metric_plane;
    int xstep = c->bpp[mp];
    int ystep = c->stride[mp]<<3;
    int s     = c->stride[mp]<<1; /* field stride */
    int w     = c->metric_w*xstep;

    if( !fa->buffer || !fb->buffer ) return;

    /* Shortcut for duplicate fields (e.g. from RFF flag) */
    if( fa->buffer == fb->buffer && pa == pb )
    {
        memset( dest, 0, c->metric_len * sizeof(int) );
        return;
    }

    a = fa->buffer->planes[mp] + pa * c->stride[mp] + c->metric_offset;
    b = fb->buffer->planes[mp] + pb * c->stride[mp] + c->metric_offset;

    for( y = c->metric_h; y; y-- )
    {
        for( x = 0; x < w; x += xstep )
        {
            *dest++ = func( a + x, b + x, s );
        }
        a += ystep; b += ystep;
    }
}