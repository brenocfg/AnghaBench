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
struct TYPE_3__ {scalar_t__ sample_rate; scalar_t__ channels; scalar_t__ chan_config; } ;
typedef  TYPE_1__ MPEG4AudioConfig ;
typedef  int /*<<< orphan*/  GetBitContext ;

/* Variables and functions */
 int AVERROR_INVALIDDATA ; 
 int /*<<< orphan*/  AV_LOG_ERROR ; 
 scalar_t__ MKBETAG (char,char,char,char) ; 
 int /*<<< orphan*/  av_log (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*,scalar_t__) ; 
 scalar_t__ get_bits (int /*<<< orphan*/ *,int) ; 
 int get_bits_left (int /*<<< orphan*/ *) ; 
 scalar_t__ get_bits_long (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  skip_bits_long (int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static int parse_config_ALS(GetBitContext *gb, MPEG4AudioConfig *c)
{
    if (get_bits_left(gb) < 112)
        return AVERROR_INVALIDDATA;

    if (get_bits_long(gb, 32) != MKBETAG('A','L','S','\0'))
        return AVERROR_INVALIDDATA;

    // override AudioSpecificConfig channel configuration and sample rate
    // which are buggy in old ALS conformance files
    c->sample_rate = get_bits_long(gb, 32);

    if (c->sample_rate <= 0) {
        av_log(NULL, AV_LOG_ERROR, "Invalid sample rate %d\n", c->sample_rate);
        return AVERROR_INVALIDDATA;
    }

    // skip number of samples
    skip_bits_long(gb, 32);

    // read number of channels
    c->chan_config = 0;
    c->channels    = get_bits(gb, 16) + 1;

    return 0;
}