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
typedef  int /*<<< orphan*/  rb ;
typedef  int apr_size_t ;
struct TYPE_3__ {int /*<<< orphan*/ * wakeup_pipe; } ;
typedef  TYPE_1__ apr_pollset_t ;

/* Variables and functions */
 scalar_t__ APR_SUCCESS ; 
 scalar_t__ apr_file_read (int /*<<< orphan*/ ,char*,int*) ; 

void apr_pollset_drain_wakeup_pipe(apr_pollset_t *pollset)
{
    char rb[512];
    apr_size_t nr = sizeof(rb);

    while (apr_file_read(pollset->wakeup_pipe[0], rb, &nr) == APR_SUCCESS) {
        /* Although we write just one byte to the other end of the pipe
         * during wakeup, multiple threads could call the wakeup.
         * So simply drain out from the input side of the pipe all
         * the data.
         */
        if (nr != sizeof(rb))
            break;
    }
}