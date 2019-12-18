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
struct TYPE_2__ {long* keys; } ;
typedef  TYPE_1__ mz_stream_pkcrypt ;

/* Variables and functions */
 int /*<<< orphan*/  mz_stream_pkcrypt_update_keys (void*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void mz_stream_pkcrypt_init_keys(void *stream, const char *password)
{
    mz_stream_pkcrypt *pkcrypt = (mz_stream_pkcrypt *)stream;

    pkcrypt->keys[0] = 305419896L;
    pkcrypt->keys[1] = 591751049L;
    pkcrypt->keys[2] = 878082192L;

    while (*password != 0)
    {
        mz_stream_pkcrypt_update_keys(stream, (uint8_t)*password);
        password += 1;
    }
}