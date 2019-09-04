#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/ * extradata; } ;
typedef  TYPE_1__ AVCodecParameters ;

/* Variables and functions */
 int AVERROR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ENOMEM ; 
 int /*<<< orphan*/  av_freep (int /*<<< orphan*/ **) ; 
 scalar_t__ ff_alloc_extradata (TYPE_1__*,int) ; 
 int ff_hex_to_data (int /*<<< orphan*/ *,char const*) ; 

__attribute__((used)) static int parse_fmtp_config(AVCodecParameters *par, const char *value)
{
    /* decode the hexa encoded parameter */
    int len = ff_hex_to_data(NULL, value);
    av_freep(&par->extradata);
    if (ff_alloc_extradata(par, len))
        return AVERROR(ENOMEM);
    ff_hex_to_data(par->extradata, value);
    return 0;
}