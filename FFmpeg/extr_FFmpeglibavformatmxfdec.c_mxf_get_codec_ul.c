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
typedef  int /*<<< orphan*/  UID ;
struct TYPE_4__ {int /*<<< orphan*/  matching_len; scalar_t__* uid; } ;
typedef  TYPE_1__ MXFCodecUL ;

/* Variables and functions */
 scalar_t__ mxf_match_uid (scalar_t__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static const MXFCodecUL *mxf_get_codec_ul(const MXFCodecUL *uls, UID *uid)
{
    while (uls->uid[0]) {
        if(mxf_match_uid(uls->uid, *uid, uls->matching_len))
            break;
        uls++;
    }
    return uls;
}