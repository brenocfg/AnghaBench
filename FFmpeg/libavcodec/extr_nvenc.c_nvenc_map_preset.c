#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {int /*<<< orphan*/  flags; int /*<<< orphan*/  guid; } ;
struct TYPE_7__ {int /*<<< orphan*/  presetGUID; } ;
struct TYPE_8__ {size_t preset; int /*<<< orphan*/  flags; TYPE_1__ init_encode_params; } ;
typedef  TYPE_2__ NvencContext ;
typedef  TYPE_3__ GUIDTuple ;

/* Variables and functions */
 int /*<<< orphan*/  BD ; 
 int /*<<< orphan*/  DEFAULT ; 
 int /*<<< orphan*/  FAST ; 
 int /*<<< orphan*/  HP ; 
 int /*<<< orphan*/  HQ ; 
 int /*<<< orphan*/  LOSSLESS_DEFAULT ; 
 int /*<<< orphan*/  LOSSLESS_HP ; 
 int /*<<< orphan*/  LOW_LATENCY_DEFAULT ; 
 int /*<<< orphan*/  LOW_LATENCY_HP ; 
 int /*<<< orphan*/  LOW_LATENCY_HQ ; 
 int /*<<< orphan*/  MEDIUM ; 
 int /*<<< orphan*/  NVENC_LOSSLESS ; 
 int /*<<< orphan*/  NVENC_LOWLATENCY ; 
 int /*<<< orphan*/  NVENC_ONE_PASS ; 
 int /*<<< orphan*/  NVENC_TWO_PASSES ; 
 TYPE_3__ PRESET (int /*<<< orphan*/ ,...) ; 
 TYPE_3__ PRESET_ALIAS (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SLOW ; 

__attribute__((used)) static void nvenc_map_preset(NvencContext *ctx)
{
    GUIDTuple presets[] = {
        PRESET(DEFAULT),
        PRESET(HP),
        PRESET(HQ),
        PRESET(BD),
        PRESET_ALIAS(SLOW,   HQ,    NVENC_TWO_PASSES),
        PRESET_ALIAS(MEDIUM, HQ,    NVENC_ONE_PASS),
        PRESET_ALIAS(FAST,   HP,    NVENC_ONE_PASS),
        PRESET(LOW_LATENCY_DEFAULT, NVENC_LOWLATENCY),
        PRESET(LOW_LATENCY_HP,      NVENC_LOWLATENCY),
        PRESET(LOW_LATENCY_HQ,      NVENC_LOWLATENCY),
        PRESET(LOSSLESS_DEFAULT,    NVENC_LOSSLESS),
        PRESET(LOSSLESS_HP,         NVENC_LOSSLESS),
    };

    GUIDTuple *t = &presets[ctx->preset];

    ctx->init_encode_params.presetGUID = t->guid;
    ctx->flags = t->flags;
}