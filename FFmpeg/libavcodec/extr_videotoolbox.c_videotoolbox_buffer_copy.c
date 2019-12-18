#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int /*<<< orphan*/  uint32_t ;
struct TYPE_3__ {int /*<<< orphan*/  bitstream_size; void* bitstream; int /*<<< orphan*/  allocated_size; } ;
typedef  TYPE_1__ VTContext ;

/* Variables and functions */
 int AVERROR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ENOMEM ; 
 void* av_fast_realloc (void*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (void*,int /*<<< orphan*/  const*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int videotoolbox_buffer_copy(VTContext *vtctx,
                                    const uint8_t *buffer,
                                    uint32_t size)
{
    void *tmp;

    tmp = av_fast_realloc(vtctx->bitstream,
                         &vtctx->allocated_size,
                         size);

    if (!tmp)
        return AVERROR(ENOMEM);

    vtctx->bitstream = tmp;
    memcpy(vtctx->bitstream, buffer, size);
    vtctx->bitstream_size = size;

    return 0;
}