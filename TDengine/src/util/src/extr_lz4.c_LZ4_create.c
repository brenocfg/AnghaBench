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
typedef  void LZ4_stream_t ;
typedef  int /*<<< orphan*/  BYTE ;

/* Variables and functions */
 scalar_t__ ALLOCATOR (int,int) ; 
 int /*<<< orphan*/  LZ4_init (void*,int /*<<< orphan*/ *) ; 

void* LZ4_create (char* inputBuffer)
{
    LZ4_stream_t* lz4ds = (LZ4_stream_t*)ALLOCATOR(8, sizeof(LZ4_stream_t));
    LZ4_init (lz4ds, (BYTE*)inputBuffer);
    return lz4ds;
}