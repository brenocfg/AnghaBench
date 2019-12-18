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
typedef  int /*<<< orphan*/  AVDictionary ;

/* Variables and functions */
 int apply_vpx_preset (int /*<<< orphan*/ **,char const*) ; 
 int /*<<< orphan*/  av_dict_set (int /*<<< orphan*/ **,char*,char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int apply_vp9_preset(AVDictionary ** av_opts, const char * preset)
{
    av_dict_set(av_opts, "row-mt", "1", 0);
    return apply_vpx_preset(av_opts, preset);
}