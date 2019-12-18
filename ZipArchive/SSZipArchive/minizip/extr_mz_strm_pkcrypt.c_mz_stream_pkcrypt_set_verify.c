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
typedef  void* uint8_t ;
struct TYPE_2__ {void* verify2; void* verify1; } ;
typedef  TYPE_1__ mz_stream_pkcrypt ;

/* Variables and functions */

void mz_stream_pkcrypt_set_verify(void *stream, uint8_t verify1, uint8_t verify2)
{
    mz_stream_pkcrypt *pkcrypt = (mz_stream_pkcrypt *)stream;
    pkcrypt->verify1 = verify1;
    pkcrypt->verify2 = verify2;
}