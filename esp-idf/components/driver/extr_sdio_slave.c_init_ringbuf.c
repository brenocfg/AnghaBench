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
typedef  int /*<<< orphan*/  uint8_t ;
typedef  scalar_t__ esp_err_t ;
typedef  int /*<<< orphan*/  buf_desc_t ;
struct TYPE_3__ {int send_queue_size; } ;
struct TYPE_4__ {int /*<<< orphan*/  sendbuf; TYPE_1__ config; } ;

/* Variables and functions */
 scalar_t__ ESP_OK ; 
 int /*<<< orphan*/  RINGBUF_GET_ALL ; 
 int /*<<< orphan*/  RINGBUF_GET_ONE ; 
 int /*<<< orphan*/  assert (int) ; 
 TYPE_2__ context ; 
 int /*<<< orphan*/ * link_desc_to_last ; 
 int /*<<< orphan*/  portMAX_DELAY ; 
 scalar_t__ sdio_ringbuf_init (int /*<<< orphan*/ *,int,int) ; 
 scalar_t__ sdio_ringbuf_recv (int /*<<< orphan*/ *,int /*<<< orphan*/ **,int /*<<< orphan*/ **,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sdio_ringbuf_return (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ sdio_ringbuf_send (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static esp_err_t init_ringbuf(void)
{
    esp_err_t ret = sdio_ringbuf_init(&context.sendbuf, sizeof(buf_desc_t), context.config.send_queue_size);
    if (ret != ESP_OK) return ret;

    esp_err_t rcv_res;
    buf_desc_t *first=NULL, *last=NULL;

    //no copy for the first descriptor
    ret = sdio_ringbuf_send(&context.sendbuf, NULL, NULL, portMAX_DELAY);
    if (ret != ESP_OK) return ret;

    //loop in the ringbuf to link all the desc one after another as a ring
    for (int i = 0; i < context.config.send_queue_size+1; i++) {
        rcv_res = sdio_ringbuf_recv(&context.sendbuf, (uint8_t**)&last, NULL, RINGBUF_GET_ONE, 0);
        assert (rcv_res == ESP_OK);
        ret = sdio_ringbuf_send(&context.sendbuf, link_desc_to_last, last, portMAX_DELAY);
        if (ret != ESP_OK) return ret;
        sdio_ringbuf_return(&context.sendbuf, (uint8_t*)last);
    }
    first = NULL;
    last = NULL;
    //clear the queue
    rcv_res = sdio_ringbuf_recv(&context.sendbuf, (uint8_t**)&first, (uint8_t**)&last, RINGBUF_GET_ALL, 0);
    assert (rcv_res == ESP_OK);
    assert(first == last); //there should be only one desc remain
    sdio_ringbuf_return(&context.sendbuf, (uint8_t*)first);
    return ESP_OK;
}