#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
typedef  scalar_t__ uint64_t ;
struct TYPE_7__ {int width; int height; } ;
struct TYPE_8__ {TYPE_2__ f; TYPE_1__* plane; } ;
typedef  TYPE_3__ hb_buffer_t ;
struct TYPE_6__ {int stride; int /*<<< orphan*/ * data; } ;

/* Variables and functions */
 scalar_t__ sse_block16 (unsigned int*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static float motion_metric( unsigned * gamma_lut, hb_buffer_t * a, hb_buffer_t * b )
{
    int bw = a->f.width / 16;
    int bh = a->f.height / 16;
    int stride = a->plane[0].stride;
    uint8_t * pa = a->plane[0].data;
    uint8_t * pb = b->plane[0].data;
    int x, y;
    uint64_t sum = 0;

    for( y = 0; y < bh; y++ )
    {
        for( x = 0; x < bw; x++ )
        {
            sum +=  sse_block16( gamma_lut, pa + y * 16 * stride + x * 16,
                                            pb + y * 16 * stride + x * 16,
                                            stride );
        }
    }
    return (float)sum / ( a->f.width * a->f.height );;
}