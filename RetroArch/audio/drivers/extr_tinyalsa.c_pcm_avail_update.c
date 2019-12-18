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
struct pcm {int dummy; } ;

/* Variables and functions */
 int pcm_mmap_avail (struct pcm*) ; 
 int /*<<< orphan*/  pcm_sync_ptr (struct pcm*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int pcm_avail_update(struct pcm *pcm)
{
   pcm_sync_ptr(pcm, 0);
   return pcm_mmap_avail(pcm);
}