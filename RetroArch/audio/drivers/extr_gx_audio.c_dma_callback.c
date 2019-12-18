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
typedef  int /*<<< orphan*/  uint32_t ;
struct TYPE_2__ {size_t dma_busy; size_t dma_next; scalar_t__* data; } ;
typedef  TYPE_1__ gx_audio_t ;

/* Variables and functions */
 int /*<<< orphan*/  AIInitDMA (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int BLOCKS ; 
 int /*<<< orphan*/  CHUNK_SIZE ; 
 int /*<<< orphan*/  DCFlushRange (scalar_t__,int /*<<< orphan*/ ) ; 
 scalar_t__ gx_audio_data ; 
 int /*<<< orphan*/  memset (scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ stop_audio ; 

__attribute__((used)) static void dma_callback(void)
{
   gx_audio_t *wa = (gx_audio_t*)gx_audio_data;

   if (stop_audio)
      return;

   /* Erase last chunk to avoid repeating audio. */
   memset(wa->data[wa->dma_busy], 0, CHUNK_SIZE);

   wa->dma_busy = wa->dma_next;
   wa->dma_next = (wa->dma_next + 1) & (BLOCKS - 1);

   DCFlushRange(wa->data[wa->dma_next], CHUNK_SIZE);

   AIInitDMA((uint32_t)wa->data[wa->dma_next], CHUNK_SIZE);
}