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
typedef  int /*<<< orphan*/  uint32_t ;
typedef  scalar_t__ ssize_t ;
typedef  int /*<<< orphan*/  esp_err_t ;

/* Variables and functions */
 int /*<<< orphan*/  ESP_FAIL ; 
 int /*<<< orphan*/  ESP_LOGE (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  ESP_OK ; 
 int /*<<< orphan*/  TAG ; 
 int /*<<< orphan*/ * malloc (scalar_t__) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/  const*,scalar_t__) ; 
 int /*<<< orphan*/  test_priv_data ; 

esp_err_t test_req_handler (uint32_t session_id,
                            const uint8_t *inbuf, ssize_t inlen,
                            uint8_t **outbuf, ssize_t *outlen,
                            void *priv_data)
{
    *outbuf = malloc(inlen);
    if (*outbuf) {
        *outlen = inlen;
        memcpy(*outbuf, inbuf, inlen);
    } else {
        ESP_LOGE(TAG, "Error allocating response outbuf");
        *outbuf = NULL;
        *outlen = 0;
    }

    uint32_t *priv = (uint32_t *) priv_data;
    if ((&test_priv_data != priv) || (test_priv_data != *priv)) {
        ESP_LOGE(TAG, "Handler private data doesn't match");
        return ESP_FAIL;
    }
    return ESP_OK;
}