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
struct TYPE_2__ {int* keys; } ;
typedef  TYPE_1__ mz_stream_pkcrypt ;

/* Variables and functions */

__attribute__((used)) static uint8_t mz_stream_pkcrypt_decrypt_byte(void *stream)
{
    mz_stream_pkcrypt *pkcrypt = (mz_stream_pkcrypt *)stream;

    unsigned temp; /* POTENTIAL BUG:  temp*(temp^1) may overflow in an */
                   /* unpredictable manner on 16-bit systems; not a problem */
                   /* with any known compiler so far, though. */

    temp = pkcrypt->keys[2] | 2;
    return (uint8_t)(((temp * (temp ^ 1)) >> 8) & 0xff);
}