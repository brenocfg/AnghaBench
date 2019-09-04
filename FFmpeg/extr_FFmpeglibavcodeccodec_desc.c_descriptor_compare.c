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
typedef  enum AVCodecID { ____Placeholder_AVCodecID } AVCodecID ;
struct TYPE_2__ {int id; } ;
typedef  TYPE_1__ AVCodecDescriptor ;

/* Variables and functions */

__attribute__((used)) static int descriptor_compare(const void *key, const void *member)
{
    enum AVCodecID id = *(const enum AVCodecID *) key;
    const AVCodecDescriptor *desc = member;

    return id - desc->id;
}