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
struct data_mbuf {int /*<<< orphan*/  outlen; int /*<<< orphan*/ * outbuf; int /*<<< orphan*/  attr_handle; } ;
typedef  int /*<<< orphan*/  ssize_t ;

/* Variables and functions */
 int ESP_ERR_NO_MEM ; 
 int /*<<< orphan*/  ESP_LOGE (int /*<<< orphan*/ ,char*) ; 
 int ESP_OK ; 
 int /*<<< orphan*/  SLIST_INSERT_HEAD (int /*<<< orphan*/ *,struct data_mbuf*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TAG ; 
 struct data_mbuf* calloc (int,int) ; 
 int /*<<< orphan*/  data_mbuf_list ; 
 struct data_mbuf* find_attr_with_handle (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  node ; 

__attribute__((used)) static int simple_ble_gatts_set_attr_value(uint16_t attr_handle, ssize_t outlen,
        uint8_t *outbuf)
{
    struct data_mbuf *attr_mbuf = find_attr_with_handle(attr_handle);
    if (!attr_mbuf) {
        attr_mbuf = calloc(1, sizeof(struct data_mbuf));
        if (!attr_mbuf) {
            ESP_LOGE(TAG, "Failed to allocate memory for storing outbuf and outlen");
            return ESP_ERR_NO_MEM;
        }
        SLIST_INSERT_HEAD(&data_mbuf_list, attr_mbuf, node);
        attr_mbuf->attr_handle = attr_handle;
    } else {
        free(attr_mbuf->outbuf);
    }
    attr_mbuf->outbuf = outbuf;
    attr_mbuf->outlen = outlen;
    return ESP_OK;
}