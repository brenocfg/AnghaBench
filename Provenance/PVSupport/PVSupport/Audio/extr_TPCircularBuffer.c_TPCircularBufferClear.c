#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  int32_t ;
typedef  int /*<<< orphan*/  TPCircularBuffer ;

/* Variables and functions */
 int /*<<< orphan*/  TPCircularBufferConsume (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ TPCircularBufferTail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

void TPCircularBufferClear(TPCircularBuffer *buffer) {
    int32_t fillCount;
    if ( TPCircularBufferTail(buffer, &fillCount) ) {
        TPCircularBufferConsume(buffer, fillCount);
    }
}