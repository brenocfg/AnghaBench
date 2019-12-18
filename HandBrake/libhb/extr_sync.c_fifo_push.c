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
typedef  int /*<<< orphan*/  hb_fifo_t ;
typedef  int /*<<< orphan*/  hb_buffer_t ;

/* Variables and functions */
 int /*<<< orphan*/  hb_buffer_close (int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  hb_fifo_push (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void fifo_push( hb_fifo_t * fifo, hb_buffer_t * buf )
{
    if (fifo != NULL)
    {
        hb_fifo_push(fifo, buf);
    }
    else
    {
        hb_buffer_close(&buf);
    }
}