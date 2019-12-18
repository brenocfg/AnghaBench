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
typedef  size_t ssize_t ;
struct TYPE_2__ {scalar_t__ rx_mode; int /*<<< orphan*/  read_lock; } ;

/* Variables and functions */
 scalar_t__ ESP_LINE_ENDINGS_CR ; 
 scalar_t__ ESP_LINE_ENDINGS_CRLF ; 
 int /*<<< orphan*/  EWOULDBLOCK ; 
 int NONE ; 
 int /*<<< orphan*/  _lock_acquire_recursive (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  _lock_release_recursive (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  errno ; 
 TYPE_1__** s_ctx ; 
 int uart_read_char (int) ; 
 int /*<<< orphan*/  uart_return_char (int,int) ; 

__attribute__((used)) static ssize_t uart_read(int fd, void* data, size_t size)
{
    assert(fd >=0 && fd < 3);
    char *data_c = (char *) data;
    size_t received = 0;
    _lock_acquire_recursive(&s_ctx[fd]->read_lock);
    while (received < size) {
        int c = uart_read_char(fd);
        if (c == '\r') {
            if (s_ctx[fd]->rx_mode == ESP_LINE_ENDINGS_CR) {
                c = '\n';
            } else if (s_ctx[fd]->rx_mode == ESP_LINE_ENDINGS_CRLF) {
                /* look ahead */
                int c2 = uart_read_char(fd);
                if (c2 == NONE) {
                    /* could not look ahead, put the current character back */
                    uart_return_char(fd, c);
                    break;
                }
                if (c2 == '\n') {
                    /* this was \r\n sequence. discard \r, return \n */
                    c = '\n';
                } else {
                    /* \r followed by something else. put the second char back,
                     * it will be processed on next iteration. return \r now.
                     */
                    uart_return_char(fd, c2);
                }
            }
        } else if (c == NONE) {
            break;
        }
        data_c[received] = (char) c;
        ++received;
        if (c == '\n') {
            break;
        }
    }
    _lock_release_recursive(&s_ctx[fd]->read_lock);
    if (received > 0) {
        return received;
    }
    errno = EWOULDBLOCK;
    return -1;
}