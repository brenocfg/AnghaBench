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
typedef  int /*<<< orphan*/  uint16_t ;
struct data_mbuf {int /*<<< orphan*/  outlen; int /*<<< orphan*/ * outbuf; } ;
typedef  int /*<<< orphan*/  ssize_t ;

/* Variables and functions */
 int ESP_ERR_NOT_FOUND ; 
 int /*<<< orphan*/  ESP_LOGE (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int ESP_OK ; 
 int /*<<< orphan*/  TAG ; 
 struct data_mbuf* find_attr_with_handle (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int simple_ble_gatts_get_attr_value(uint16_t attr_handle, ssize_t
        *outlen, uint8_t **outbuf)
{
    struct data_mbuf *attr_mbuf = find_attr_with_handle(attr_handle);
    if (!attr_mbuf) {
        ESP_LOGE(TAG, "Outbuf with handle %d not found", attr_handle);
        return ESP_ERR_NOT_FOUND;
    }
    *outbuf = attr_mbuf->outbuf;
    *outlen = attr_mbuf->outlen;
    return ESP_OK;
}