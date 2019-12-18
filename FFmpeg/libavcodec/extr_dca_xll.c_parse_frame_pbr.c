#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
struct TYPE_5__ {int pbr_length; scalar_t__ pbr_buffer; scalar_t__ pbr_delay; scalar_t__ frame_size; } ;
typedef  TYPE_1__ DCAXllDecoder ;
typedef  int /*<<< orphan*/  DCAExssAsset ;

/* Variables and functions */
 int AVERROR (int /*<<< orphan*/ ) ; 
 int DCA_XLL_PBR_BUFFER_MAX ; 
 int /*<<< orphan*/  EAGAIN ; 
 int /*<<< orphan*/  EINVAL ; 
 int /*<<< orphan*/  ENOSPC ; 
 int /*<<< orphan*/  clear_pbr (TYPE_1__*) ; 
 int /*<<< orphan*/  memcpy (scalar_t__,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  memmove (scalar_t__,scalar_t__,scalar_t__) ; 
 int parse_frame (TYPE_1__*,scalar_t__,scalar_t__,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int parse_frame_pbr(DCAXllDecoder *s, uint8_t *data, int size, DCAExssAsset *asset)
{
    int ret;

    if (size > DCA_XLL_PBR_BUFFER_MAX - s->pbr_length) {
        ret = AVERROR(ENOSPC);
        goto fail;
    }

    memcpy(s->pbr_buffer + s->pbr_length, data, size);
    s->pbr_length += size;

    // Respect decoding delay after synchronization error
    if (s->pbr_delay > 0 && --s->pbr_delay)
        return AVERROR(EAGAIN);

    if ((ret = parse_frame(s, s->pbr_buffer, s->pbr_length, asset)) < 0)
        goto fail;

    if (s->frame_size > s->pbr_length) {
        ret = AVERROR(EINVAL);
        goto fail;
    }

    if (s->frame_size == s->pbr_length) {
        // End of PBR smoothing period
        clear_pbr(s);
    } else {
        s->pbr_length -= s->frame_size;
        memmove(s->pbr_buffer, s->pbr_buffer + s->frame_size, s->pbr_length);
    }

    return 0;

fail:
    // For now, throw out all PBR state on failure.
    // Perhaps we can be smarter and try to resync somehow.
    clear_pbr(s);
    return ret;
}