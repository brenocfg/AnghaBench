#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {unsigned long cBuffers; int /*<<< orphan*/ * pBuffers; int /*<<< orphan*/  ulVersion; } ;
typedef  TYPE_1__ SecBufferDesc ;
typedef  int /*<<< orphan*/  SecBuffer ;

/* Variables and functions */
 int /*<<< orphan*/  SECBUFFER_VERSION ; 

__attribute__((used)) static void init_sec_buffer_desc(SecBufferDesc *desc, SecBuffer *buffers,
                                 unsigned long buffer_count)
{
    desc->ulVersion = SECBUFFER_VERSION;
    desc->pBuffers = buffers;
    desc->cBuffers = buffer_count;
}