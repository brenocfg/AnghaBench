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
typedef  scalar_t__ uint8_t ;
struct TYPE_7__ {int reduced_width; int width; TYPE_3__* image; int /*<<< orphan*/  gb; } ;
typedef  TYPE_2__ WebPContext ;
struct TYPE_8__ {int size_reduction; TYPE_1__* frame; } ;
struct TYPE_6__ {int width; scalar_t__** data; } ;
typedef  TYPE_3__ ImageContext ;

/* Variables and functions */
 size_t IMAGE_ROLE_COLOR_INDEXING ; 
 int decode_entropy_coded_image (TYPE_2__*,size_t,int,int) ; 
 int get_bits (int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static int parse_transform_color_indexing(WebPContext *s)
{
    ImageContext *img;
    int width_bits, index_size, ret, x;
    uint8_t *ct;

    index_size = get_bits(&s->gb, 8) + 1;

    if (index_size <= 2)
        width_bits = 3;
    else if (index_size <= 4)
        width_bits = 2;
    else if (index_size <= 16)
        width_bits = 1;
    else
        width_bits = 0;

    ret = decode_entropy_coded_image(s, IMAGE_ROLE_COLOR_INDEXING,
                                     index_size, 1);
    if (ret < 0)
        return ret;

    img = &s->image[IMAGE_ROLE_COLOR_INDEXING];
    img->size_reduction = width_bits;
    if (width_bits > 0)
        s->reduced_width = (s->width + ((1 << width_bits) - 1)) >> width_bits;

    /* color index values are delta-coded */
    ct  = img->frame->data[0] + 4;
    for (x = 4; x < img->frame->width * 4; x++, ct++)
        ct[0] += ct[-4];

    return 0;
}