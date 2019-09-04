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
struct TYPE_3__ {int /*<<< orphan*/  flex_ratio_max; int /*<<< orphan*/  flex_ratio_min; int /*<<< orphan*/  flex_ratio; int /*<<< orphan*/  busFreq; int /*<<< orphan*/  bus2tsc; int /*<<< orphan*/  tscGranularity; int /*<<< orphan*/  tscFCvtn2t; int /*<<< orphan*/  tscFCvtt2n; int /*<<< orphan*/  tscFreq; int /*<<< orphan*/  busFCvtn2t; int /*<<< orphan*/  busFCvtt2n; } ;
typedef  TYPE_1__ tscInfo_t ;

/* Variables and functions */
 int /*<<< orphan*/  bus2tsc ; 
 int /*<<< orphan*/  busFCvtn2t ; 
 int /*<<< orphan*/  busFCvtt2n ; 
 int /*<<< orphan*/  busFreq ; 
 int /*<<< orphan*/  flex_ratio ; 
 int /*<<< orphan*/  flex_ratio_max ; 
 int /*<<< orphan*/  flex_ratio_min ; 
 int /*<<< orphan*/  tscFCvtn2t ; 
 int /*<<< orphan*/  tscFCvtt2n ; 
 int /*<<< orphan*/  tscFreq ; 
 int /*<<< orphan*/  tscGranularity ; 

void
tsc_get_info(tscInfo_t *info)
{
	info->busFCvtt2n     = busFCvtt2n;
	info->busFCvtn2t     = busFCvtn2t;
	info->tscFreq        = tscFreq;
	info->tscFCvtt2n     = tscFCvtt2n;
	info->tscFCvtn2t     = tscFCvtn2t;
	info->tscGranularity = tscGranularity;
	info->bus2tsc        = bus2tsc;
	info->busFreq        = busFreq;
	info->flex_ratio     = flex_ratio;
	info->flex_ratio_min = flex_ratio_min;
	info->flex_ratio_max = flex_ratio_max;
}