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
typedef  int /*<<< orphan*/  xSemaphoreHandle ;
typedef  int /*<<< orphan*/  output ;
typedef  int /*<<< orphan*/  input ;

/* Variables and functions */
 int /*<<< orphan*/  ESP_LOGI (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  SHA2_512 ; 
 int /*<<< orphan*/  TAG ; 
 int /*<<< orphan*/  TEST_ASSERT_EQUAL_MEMORY_MESSAGE (unsigned char*,unsigned char*,int,char*) ; 
 int /*<<< orphan*/  esp_sha (int /*<<< orphan*/ ,unsigned char const*,int,unsigned char*) ; 
 int exit_flag ; 
 int /*<<< orphan*/  memcpy (unsigned char*,unsigned char*,int) ; 
 int /*<<< orphan*/  memset (unsigned char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  vTaskDelete (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  xSemaphoreGive (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void sha_task(void *pvParameters)
{
    xSemaphoreHandle *sema = (xSemaphoreHandle *) pvParameters;
    ESP_LOGI(TAG, "sha_task is started");
    const char *input = "Space!#$%&()*+,-.0123456789:;<=>?@ABCDEFGHIJKLMNOPQRSTUVWXYZ[]^_abcdefghijklmnopqrstuvwxyz~DEL0123456789";
    unsigned char output[64];
    unsigned char output_origin[64];
    esp_sha(SHA2_512, (const unsigned char *)input, sizeof(input), output);
    memcpy(output_origin, output, sizeof(output));
    while (exit_flag == false) {
        memset(output, 0, sizeof(output));
        esp_sha(SHA2_512, (const unsigned char *)input, sizeof(input), output);
        TEST_ASSERT_EQUAL_MEMORY_MESSAGE(output, output_origin, sizeof(output), "SHA256 must match");
    }
    xSemaphoreGive(*sema);
    vTaskDelete(NULL);
}