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
typedef  int /*<<< orphan*/  uint8_t ;

/* Variables and functions */
 int /*<<< orphan*/  check_ts_sync (int /*<<< orphan*/  const*) ; 

__attribute__((used)) static int have_ts_sync(const uint8_t *buf, int psize, int count)
{
    int ii;
    for ( ii = 0; ii < count; ii++ )
    {
        if ( !check_ts_sync(&buf[ii*psize]) )
            return 0;
    }
    return 1;
}