#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {TYPE_1__* image; int /*<<< orphan*/  height; int /*<<< orphan*/  width; } ;
typedef  TYPE_2__ WebPContext ;
struct TYPE_5__ {int size_reduction; } ;

/* Variables and functions */
 size_t IMAGE_ROLE_PREDICTOR ; 
 int /*<<< orphan*/  PARSE_BLOCK_SIZE (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int decode_entropy_coded_image (TYPE_2__*,size_t,int,int) ; 

__attribute__((used)) static int parse_transform_predictor(WebPContext *s)
{
    int block_bits, blocks_w, blocks_h, ret;

    PARSE_BLOCK_SIZE(s->width, s->height);

    ret = decode_entropy_coded_image(s, IMAGE_ROLE_PREDICTOR, blocks_w,
                                     blocks_h);
    if (ret < 0)
        return ret;

    s->image[IMAGE_ROLE_PREDICTOR].size_reduction = block_bits;

    return 0;
}