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
struct TYPE_6__ {scalar_t__ last_ver; scalar_t__ last_crc; scalar_t__ crc; } ;
struct TYPE_5__ {scalar_t__ version; } ;
typedef  TYPE_1__ SectionHeader ;
typedef  TYPE_2__ MpegTSSectionFilter ;

/* Variables and functions */

__attribute__((used)) static int skip_identical(const SectionHeader *h, MpegTSSectionFilter *tssf)
{
    if (h->version == tssf->last_ver && tssf->last_crc == tssf->crc)
        return 1;

    tssf->last_ver = h->version;
    tssf->last_crc = tssf->crc;

    return 0;
}