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
typedef  int /*<<< orphan*/  int64_t ;
struct TYPE_4__ {int /*<<< orphan*/  pb; } ;
typedef  int /*<<< orphan*/  AVStream ;
typedef  TYPE_1__ AVFormatContext ;

/* Variables and functions */
 int /*<<< orphan*/  mxf_generic_sound_descriptor_key ; 
 int /*<<< orphan*/  mxf_update_klv_size (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mxf_write_generic_sound_common (TYPE_1__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void mxf_write_generic_sound_desc(AVFormatContext *s, AVStream *st)
{
    int64_t pos = mxf_write_generic_sound_common(s, st, mxf_generic_sound_descriptor_key);
    mxf_update_klv_size(s->pb, pos);
}