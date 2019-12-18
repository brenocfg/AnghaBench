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
typedef  int /*<<< orphan*/  LZ4_stream_t_internal ;
typedef  int /*<<< orphan*/  LZ4_stream_t ;

/* Variables and functions */
 scalar_t__ ALLOC (int) ; 
 int /*<<< orphan*/  DEBUGLOG (int,char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  LZ4_STATIC_ASSERT (int) ; 
 int LZ4_STREAMSIZE ; 
 int /*<<< orphan*/  LZ4_resetStream (int /*<<< orphan*/ *) ; 

LZ4_stream_t* LZ4_createStream(void)
{
    LZ4_stream_t* lz4s = (LZ4_stream_t*)ALLOC(sizeof(LZ4_stream_t));
    LZ4_STATIC_ASSERT(LZ4_STREAMSIZE >= sizeof(LZ4_stream_t_internal));    /* A compilation error here means LZ4_STREAMSIZE is not large enough */
    DEBUGLOG(4, "LZ4_createStream %p", lz4s);
    if (lz4s == NULL) return NULL;
    LZ4_resetStream(lz4s);
    return lz4s;
}