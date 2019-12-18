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
 int /*<<< orphan*/  printf (char*,...) ; 
 int /*<<< orphan*/  wait_user_control (char*,int /*<<< orphan*/ ) ; 

void unity_wait_for_signal_param(const char* signal_name, char* parameter_buf, uint8_t buf_len)
{
    printf("Waiting for signal: [%s]!\n", signal_name);
    if (parameter_buf == NULL) {
        printf("Please press \"Enter\" key once any board send this signal.\n");
    } else {
        printf("Please input parameter value from any board send this signal and press \"Enter\" key.\n");
    }
    wait_user_control(parameter_buf, buf_len);
}