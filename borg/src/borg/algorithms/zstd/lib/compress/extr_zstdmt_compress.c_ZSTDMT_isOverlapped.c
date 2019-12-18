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
struct TYPE_5__ {int size; scalar_t__ start; } ;
typedef  TYPE_1__ range_t ;
struct TYPE_6__ {int capacity; scalar_t__ start; } ;
typedef  TYPE_2__ buffer_t ;
typedef  int /*<<< orphan*/  BYTE ;

/* Variables and functions */

__attribute__((used)) static int ZSTDMT_isOverlapped(buffer_t buffer, range_t range)
{
    BYTE const* const bufferStart = (BYTE const*)buffer.start;
    BYTE const* const bufferEnd = bufferStart + buffer.capacity;
    BYTE const* const rangeStart = (BYTE const*)range.start;
    BYTE const* const rangeEnd = rangeStart + range.size;

    if (rangeStart == NULL || bufferStart == NULL)
        return 0;
    /* Empty ranges cannot overlap */
    if (bufferStart == bufferEnd || rangeStart == rangeEnd)
        return 0;

    return bufferStart < rangeEnd && rangeStart < bufferEnd;
}