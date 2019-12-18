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
typedef  int /*<<< orphan*/  HEVCSEI ;
typedef  int /*<<< orphan*/  HEVCParamSets ;
typedef  int /*<<< orphan*/  GetBitContext ;

/* Variables and functions */
 int decode_nal_sei_message (int /*<<< orphan*/ *,void*,int /*<<< orphan*/ *,int /*<<< orphan*/  const*,int) ; 
 scalar_t__ more_rbsp_data (int /*<<< orphan*/ *) ; 

int ff_hevc_decode_nal_sei(GetBitContext *gb, void *logctx, HEVCSEI *s,
                           const HEVCParamSets *ps, int type)
{
    int ret;

    do {
        ret = decode_nal_sei_message(gb, logctx, s, ps, type);
        if (ret < 0)
            return ret;
    } while (more_rbsp_data(gb));
    return 1;
}