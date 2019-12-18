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
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int /*<<< orphan*/  uint32_t ;
typedef  int /*<<< orphan*/  ssize_t ;
struct TYPE_2__ {int /*<<< orphan*/  ver; } ;
typedef  TYPE_1__ protocomm_t ;

/* Variables and functions */
 int ESP_ERR_NO_MEM ; 
 int /*<<< orphan*/  ESP_LOGE (int /*<<< orphan*/ ,char*) ; 
 int ESP_OK ; 
 int /*<<< orphan*/  TAG ; 
 int /*<<< orphan*/ * malloc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strlen (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int protocomm_version_handler(uint32_t session_id,
                                     const uint8_t *inbuf, ssize_t inlen,
                                     uint8_t **outbuf, ssize_t *outlen,
                                     void *priv_data)
{
    protocomm_t *pc = (protocomm_t *) priv_data;
    if (!pc->ver) {
        *outlen = 0;
        *outbuf = NULL;
        return ESP_OK;
    }

    /* Output is a non null terminated string with length specified */
    *outlen = strlen(pc->ver);
    *outbuf = malloc(*outlen);
    if (outbuf == NULL) {
        ESP_LOGE(TAG, "Failed to allocate memory for version response");
        return ESP_ERR_NO_MEM;
    }

    memcpy(*outbuf, pc->ver, *outlen);
    return ESP_OK;
}