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
typedef  int /*<<< orphan*/  uint16_t ;
typedef  int esp_err_t ;

/* Variables and functions */
#define  ESP_ERR_INVALID_ARG 130 
#define  ESP_ERR_INVALID_STATE 129 
#define  ESP_OK 128 
 int /*<<< orphan*/  STATUS__InternalError ; 
 int /*<<< orphan*/  STATUS__InvalidArgument ; 
 int /*<<< orphan*/  STATUS__InvalidProto ; 
 int /*<<< orphan*/  STATUS__Success ; 

__attribute__((used)) static uint16_t err_to_status(esp_err_t err)
{
    uint16_t status;
    switch (err) {
        case ESP_OK:
            status = STATUS__Success;
            break;
        case ESP_ERR_INVALID_ARG:
            status = STATUS__InvalidArgument;
            break;
        case ESP_ERR_INVALID_STATE:
            status = STATUS__InvalidProto;
            break;
        default:
            status = STATUS__InternalError;
    }
    return status;
}