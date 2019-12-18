#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
struct TYPE_4__ {int len; int /*<<< orphan*/  magic; int /*<<< orphan*/  state; int /*<<< orphan*/  dest_mac; scalar_t__ buffer; } ;
typedef  TYPE_1__ example_espnow_send_param_t ;
struct TYPE_5__ {size_t type; scalar_t__ crc; int /*<<< orphan*/  payload; int /*<<< orphan*/  magic; scalar_t__ seq_num; int /*<<< orphan*/  state; } ;
typedef  TYPE_2__ example_espnow_data_t ;

/* Variables and functions */
 size_t EXAMPLE_ESPNOW_DATA_BROADCAST ; 
 size_t EXAMPLE_ESPNOW_DATA_UNICAST ; 
 scalar_t__ IS_BROADCAST_ADDR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  UINT16_MAX ; 
 int /*<<< orphan*/  assert (int) ; 
 scalar_t__ esp_crc16_le (int /*<<< orphan*/ ,int /*<<< orphan*/  const*,int) ; 
 int /*<<< orphan*/  esp_fill_random (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/ * s_example_espnow_seq ; 

void example_espnow_data_prepare(example_espnow_send_param_t *send_param)
{
    example_espnow_data_t *buf = (example_espnow_data_t *)send_param->buffer;

    assert(send_param->len >= sizeof(example_espnow_data_t));

    buf->type = IS_BROADCAST_ADDR(send_param->dest_mac) ? EXAMPLE_ESPNOW_DATA_BROADCAST : EXAMPLE_ESPNOW_DATA_UNICAST;
    buf->state = send_param->state;
    buf->seq_num = s_example_espnow_seq[buf->type]++;
    buf->crc = 0;
    buf->magic = send_param->magic;
    /* Fill all remaining bytes after the data with random values */
    esp_fill_random(buf->payload, send_param->len - sizeof(example_espnow_data_t));
    buf->crc = esp_crc16_le(UINT16_MAX, (uint8_t const *)buf, send_param->len);
}