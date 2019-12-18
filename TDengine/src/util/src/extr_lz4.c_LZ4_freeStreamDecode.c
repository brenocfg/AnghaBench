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
typedef  int /*<<< orphan*/  LZ4_streamDecode_t ;

/* Variables and functions */
 int /*<<< orphan*/  FREEMEM (int /*<<< orphan*/ *) ; 

int LZ4_freeStreamDecode (LZ4_streamDecode_t* LZ4_stream)
{
    if (!LZ4_stream) return 0;   /* support free on NULL */
    FREEMEM(LZ4_stream);
    return 0;
}