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
struct TYPE_3__ {scalar_t__ disposition; } ;
typedef  TYPE_1__ AVStream ;

/* Variables and functions */
 scalar_t__ AV_DISPOSITION_ATTACHED_PIC ; 

__attribute__((used)) static int is_cover_image(const AVStream *st)
{
    /* Eg. AV_DISPOSITION_ATTACHED_PIC | AV_DISPOSITION_TIMED_THUMBNAILS
     * is encoded as sparse video track */
    return st && st->disposition == AV_DISPOSITION_ATTACHED_PIC;
}