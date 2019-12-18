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
typedef  int /*<<< orphan*/  uint8 ;
struct TYPE_2__ {int /*<<< orphan*/  status; int /*<<< orphan*/  volume; int /*<<< orphan*/  scanOffset; int /*<<< orphan*/  lba; int /*<<< orphan*/  index; int /*<<< orphan*/  latency; int /*<<< orphan*/  cycles; } ;

/* Variables and functions */
 TYPE_1__ cdd ; 
 int /*<<< orphan*/  save_param (int /*<<< orphan*/ *,int) ; 

int cdd_context_save(uint8 *state)
{
  int bufferptr = 0;

  save_param(&cdd.cycles, sizeof(cdd.cycles));
  save_param(&cdd.latency, sizeof(cdd.latency));
  save_param(&cdd.index, sizeof(cdd.index));
  save_param(&cdd.lba, sizeof(cdd.lba));
  save_param(&cdd.scanOffset, sizeof(cdd.scanOffset));
  save_param(&cdd.volume, sizeof(cdd.volume));
  save_param(&cdd.status, sizeof(cdd.status));

  return bufferptr;
}