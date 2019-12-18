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
struct TYPE_3__ {int pbr_length; int pbr_delay; scalar_t__ pbr_buffer; } ;
typedef  TYPE_1__ DCAXllDecoder ;

/* Variables and functions */
 int AVERROR (int /*<<< orphan*/ ) ; 
 scalar_t__ AV_INPUT_BUFFER_PADDING_SIZE ; 
 int DCA_XLL_PBR_BUFFER_MAX ; 
 int /*<<< orphan*/  ENOMEM ; 
 int /*<<< orphan*/  ENOSPC ; 
 scalar_t__ av_malloc (scalar_t__) ; 
 int /*<<< orphan*/  memcpy (scalar_t__,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static int copy_to_pbr(DCAXllDecoder *s, uint8_t *data, int size, int delay)
{
    if (size > DCA_XLL_PBR_BUFFER_MAX)
        return AVERROR(ENOSPC);

    if (!s->pbr_buffer && !(s->pbr_buffer = av_malloc(DCA_XLL_PBR_BUFFER_MAX + AV_INPUT_BUFFER_PADDING_SIZE)))
        return AVERROR(ENOMEM);

    memcpy(s->pbr_buffer, data, size);
    s->pbr_length = size;
    s->pbr_delay = delay;
    return 0;
}