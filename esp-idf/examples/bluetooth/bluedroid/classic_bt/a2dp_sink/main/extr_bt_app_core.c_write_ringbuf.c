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
typedef  int /*<<< orphan*/  portTickType ;
typedef  scalar_t__ BaseType_t ;

/* Variables and functions */
 scalar_t__ portMAX_DELAY ; 
 int /*<<< orphan*/  s_ringbuf_i2s ; 
 scalar_t__ xRingbufferSend (int /*<<< orphan*/ ,void*,size_t,int /*<<< orphan*/ ) ; 

size_t write_ringbuf(const uint8_t *data, size_t size)
{
    BaseType_t done = xRingbufferSend(s_ringbuf_i2s, (void *)data, size, (portTickType)portMAX_DELAY);
    if(done){
        return size;
    } else {
        return 0;
    }
}