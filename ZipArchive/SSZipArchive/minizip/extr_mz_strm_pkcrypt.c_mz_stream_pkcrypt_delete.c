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
typedef  int /*<<< orphan*/  mz_stream_pkcrypt ;

/* Variables and functions */
 int /*<<< orphan*/  MZ_FREE (int /*<<< orphan*/ *) ; 

void mz_stream_pkcrypt_delete(void **stream)
{
    mz_stream_pkcrypt *pkcrypt = NULL;
    if (stream == NULL)
        return;
    pkcrypt = (mz_stream_pkcrypt *)*stream;
    if (pkcrypt != NULL)
        MZ_FREE(pkcrypt);
    *stream = NULL;
}