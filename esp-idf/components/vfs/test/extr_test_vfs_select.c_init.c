#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int loopback; } ;
struct TYPE_4__ {TYPE_1__ conf0; } ;

/* Variables and functions */
 int /*<<< orphan*/  O_RDWR ; 
 int /*<<< orphan*/  TEST_ASSERT_NOT_EQUAL_MESSAGE (int,int,char*) ; 
 TYPE_2__ UART1 ; 
 int /*<<< orphan*/  esp_vfs_dev_uart_use_driver (int) ; 
 int open (char*,int /*<<< orphan*/ ) ; 
 int socket_init () ; 
 int /*<<< orphan*/  test_case_uses_tcpip () ; 
 int /*<<< orphan*/  uart1_init () ; 

__attribute__((used)) static void init(int *uart_fd, int *socket_fd)
{
    test_case_uses_tcpip();

    uart1_init();
    UART1.conf0.loopback = 1;

    *uart_fd = open("/dev/uart/1", O_RDWR);
    TEST_ASSERT_NOT_EQUAL_MESSAGE(*uart_fd, -1, "Cannot open UART");

    esp_vfs_dev_uart_use_driver(1);

    *socket_fd = socket_init();
}