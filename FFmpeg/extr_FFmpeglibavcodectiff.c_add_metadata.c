#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/  le; int /*<<< orphan*/  gb; } ;
typedef  TYPE_1__ TiffContext ;
struct TYPE_6__ {int /*<<< orphan*/  metadata; } ;
typedef  TYPE_2__ AVFrame ;

/* Variables and functions */
 int AVERROR_INVALIDDATA ; 
#define  TIFF_DOUBLE 130 
#define  TIFF_SHORT 129 
#define  TIFF_STRING 128 
 int ff_tadd_doubles_metadata (int,char const*,char const*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int ff_tadd_shorts_metadata (int,char const*,char const*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int ff_tadd_string_metadata (int,char const*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int add_metadata(int count, int type,
                        const char *name, const char *sep, TiffContext *s, AVFrame *frame)
{
    switch(type) {
    case TIFF_DOUBLE: return ff_tadd_doubles_metadata(count, name, sep, &s->gb, s->le, &frame->metadata);
    case TIFF_SHORT : return ff_tadd_shorts_metadata(count, name, sep, &s->gb, s->le, 0, &frame->metadata);
    case TIFF_STRING: return ff_tadd_string_metadata(count, name, &s->gb, s->le, &frame->metadata);
    default         : return AVERROR_INVALIDDATA;
    };
}