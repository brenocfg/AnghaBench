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
typedef  int /*<<< orphan*/  esp_err_t ;

/* Variables and functions */
 int /*<<< orphan*/  ESP_OK ; 
 int /*<<< orphan*/  LEDC_CHANNEL_0 ; 
 int /*<<< orphan*/  LEDC_CHANNEL_1 ; 
 int /*<<< orphan*/  LEDC_CHANNEL_2 ; 
 int /*<<< orphan*/  LEDC_LOW_SPEED_MODE ; 
#define  MESH_LIGHT_BLUE 134 
#define  MESH_LIGHT_GREEN 133 
#define  MESH_LIGHT_INIT 132 
#define  MESH_LIGHT_PINK 131 
#define  MESH_LIGHT_RED 130 
#define  MESH_LIGHT_WARNING 129 
#define  MESH_LIGHT_YELLOW 128 
 int /*<<< orphan*/  ledc_set_duty (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ledc_update_duty (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

esp_err_t mesh_light_set(int color)
{
    switch (color) {
    case MESH_LIGHT_RED:
        /* Red */
        ledc_set_duty(LEDC_LOW_SPEED_MODE, LEDC_CHANNEL_0, 3000);
        ledc_set_duty(LEDC_LOW_SPEED_MODE, LEDC_CHANNEL_1, 0);
        ledc_set_duty(LEDC_LOW_SPEED_MODE, LEDC_CHANNEL_2, 0);
        break;
    case MESH_LIGHT_GREEN:
        /* Green */
        ledc_set_duty(LEDC_LOW_SPEED_MODE, LEDC_CHANNEL_0, 0);
        ledc_set_duty(LEDC_LOW_SPEED_MODE, LEDC_CHANNEL_1, 3000);
        ledc_set_duty(LEDC_LOW_SPEED_MODE, LEDC_CHANNEL_2, 0);
        break;
    case MESH_LIGHT_BLUE:
        /* Blue */
        ledc_set_duty(LEDC_LOW_SPEED_MODE, LEDC_CHANNEL_0, 0);
        ledc_set_duty(LEDC_LOW_SPEED_MODE, LEDC_CHANNEL_1, 0);
        ledc_set_duty(LEDC_LOW_SPEED_MODE, LEDC_CHANNEL_2, 3000);
        break;
    case MESH_LIGHT_YELLOW:
        /* Yellow */
        ledc_set_duty(LEDC_LOW_SPEED_MODE, LEDC_CHANNEL_0, 3000);
        ledc_set_duty(LEDC_LOW_SPEED_MODE, LEDC_CHANNEL_1, 3000);
        ledc_set_duty(LEDC_LOW_SPEED_MODE, LEDC_CHANNEL_2, 0);
        break;
    case MESH_LIGHT_PINK:
        /* Pink */
        ledc_set_duty(LEDC_LOW_SPEED_MODE, LEDC_CHANNEL_0, 3000);
        ledc_set_duty(LEDC_LOW_SPEED_MODE, LEDC_CHANNEL_1, 0);
        ledc_set_duty(LEDC_LOW_SPEED_MODE, LEDC_CHANNEL_2, 3000);
        break;
    case MESH_LIGHT_INIT:
        /* can't say */
        ledc_set_duty(LEDC_LOW_SPEED_MODE, LEDC_CHANNEL_0, 0);
        ledc_set_duty(LEDC_LOW_SPEED_MODE, LEDC_CHANNEL_1, 3000);
        ledc_set_duty(LEDC_LOW_SPEED_MODE, LEDC_CHANNEL_2, 3000);
        break;
    case MESH_LIGHT_WARNING:
        /* warning */
        ledc_set_duty(LEDC_LOW_SPEED_MODE, LEDC_CHANNEL_0, 3000);
        ledc_set_duty(LEDC_LOW_SPEED_MODE, LEDC_CHANNEL_1, 3000);
        ledc_set_duty(LEDC_LOW_SPEED_MODE, LEDC_CHANNEL_2, 3000);
        break;
    default:
        /* off */
        ledc_set_duty(LEDC_LOW_SPEED_MODE, LEDC_CHANNEL_0, 0);
        ledc_set_duty(LEDC_LOW_SPEED_MODE, LEDC_CHANNEL_1, 0);
        ledc_set_duty(LEDC_LOW_SPEED_MODE, LEDC_CHANNEL_2, 0);
    }

    ledc_update_duty(LEDC_LOW_SPEED_MODE, LEDC_CHANNEL_0);
    ledc_update_duty(LEDC_LOW_SPEED_MODE, LEDC_CHANNEL_1);
    ledc_update_duty(LEDC_LOW_SPEED_MODE, LEDC_CHANNEL_2);

    return ESP_OK;
}