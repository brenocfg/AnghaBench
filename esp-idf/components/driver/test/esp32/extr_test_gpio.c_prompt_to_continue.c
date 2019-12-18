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
typedef  int /*<<< orphan*/  sign ;

/* Variables and functions */
 scalar_t__ OK ; 
 int /*<<< orphan*/  UartRxString (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  printf (char*,char const*) ; 
 scalar_t__ strlen (char*) ; 
 scalar_t__ uart_rx_one_char (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void prompt_to_continue(const char* str)
{
    printf("%s , please press \"Enter\" to go on!\n", str);
    char sign[5] = {0};
    while(strlen(sign) == 0) {
        /* Flush anything already in the RX buffer */
        while(uart_rx_one_char((uint8_t *) sign) == OK) {
        }
        /* Read line */
        UartRxString((uint8_t*) sign, sizeof(sign) - 1);
    }
}