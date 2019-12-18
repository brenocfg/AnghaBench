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
typedef  int uint8_t ;
struct TYPE_2__ {scalar_t__ non_blocking; } ;

/* Variables and functions */
 int NONE ; 
 int portMAX_DELAY ; 
 TYPE_1__** s_ctx ; 
 int uart_read_bytes (int,int*,int,int) ; 

__attribute__((used)) static int uart_rx_char_via_driver(int fd)
{
    uint8_t c;
    int timeout = s_ctx[fd]->non_blocking ? 0 : portMAX_DELAY;
    int n = uart_read_bytes(fd, &c, 1, timeout);
    if (n <= 0) {
        return NONE;
    }
    return c;
}