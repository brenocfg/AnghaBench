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
typedef  scalar_t__ ssize_t ;
struct TYPE_3__ {scalar_t__ INFO_OUTPUT_FORMAT_CHANGED; } ;
typedef  TYPE_1__ FFAMediaCodec ;

/* Variables and functions */

int ff_AMediaCodec_infoOutputFormatChanged(FFAMediaCodec *codec, ssize_t idx)
{
    return idx == codec->INFO_OUTPUT_FORMAT_CHANGED;
}