#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int /*<<< orphan*/  mChannelLabel; } ;
typedef  TYPE_1__ AudioChannelDescription ;

/* Variables and functions */
 int ffat_get_channel_id (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ffat_compare_channel_descriptions(const void* a, const void* b)
{
    const AudioChannelDescription* da = a;
    const AudioChannelDescription* db = b;
    return ffat_get_channel_id(da->mChannelLabel) - ffat_get_channel_id(db->mChannelLabel);
}