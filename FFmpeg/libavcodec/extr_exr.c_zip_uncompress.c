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
struct TYPE_6__ {int /*<<< orphan*/  (* reorder_pixels ) (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ;int /*<<< orphan*/  (* predictor ) (int /*<<< orphan*/ ,int) ;} ;
struct TYPE_8__ {TYPE_1__ dsp; } ;
struct TYPE_7__ {int /*<<< orphan*/  tmp; int /*<<< orphan*/  uncompressed_data; } ;
typedef  TYPE_2__ EXRThreadData ;
typedef  TYPE_3__ EXRContext ;

/* Variables and functions */
 int AVERROR_INVALIDDATA ; 
 scalar_t__ Z_OK ; 
 int /*<<< orphan*/  av_assert1 (int) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  stub2 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 scalar_t__ uncompress (int /*<<< orphan*/ ,unsigned long*,int /*<<< orphan*/  const*,int) ; 

__attribute__((used)) static int zip_uncompress(EXRContext *s, const uint8_t *src, int compressed_size,
                          int uncompressed_size, EXRThreadData *td)
{
    unsigned long dest_len = uncompressed_size;

    if (uncompress(td->tmp, &dest_len, src, compressed_size) != Z_OK ||
        dest_len != uncompressed_size)
        return AVERROR_INVALIDDATA;

    av_assert1(uncompressed_size % 2 == 0);

    s->dsp.predictor(td->tmp, uncompressed_size);
    s->dsp.reorder_pixels(td->uncompressed_data, td->tmp, uncompressed_size);

    return 0;
}