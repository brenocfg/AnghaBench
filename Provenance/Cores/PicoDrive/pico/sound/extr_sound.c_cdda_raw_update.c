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
struct TYPE_2__ {int /*<<< orphan*/ * cdda_stream; } ;

/* Variables and functions */
 TYPE_1__* Pico_mcd ; 
 int PsndRate ; 
 scalar_t__ cdda_out_buffer ; 
 int /*<<< orphan*/  memset (char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mix_16h_to_32 (int*,scalar_t__,int) ; 
 int /*<<< orphan*/  mix_16h_to_32_s1 (int*,scalar_t__,int) ; 
 int /*<<< orphan*/  mix_16h_to_32_s2 (int*,scalar_t__,int) ; 
 int pm_read (scalar_t__,int,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void cdda_raw_update(int *buffer, int length)
{
  int ret, cdda_bytes, mult = 1;

  cdda_bytes = length*4;
  if (PsndRate <= 22050 + 100) mult = 2;
  if (PsndRate <  22050 - 100) mult = 4;
  cdda_bytes *= mult;

  ret = pm_read(cdda_out_buffer, cdda_bytes, Pico_mcd->cdda_stream);
  if (ret < cdda_bytes) {
    memset((char *)cdda_out_buffer + ret, 0, cdda_bytes - ret);
    Pico_mcd->cdda_stream = NULL;
    return;
  }

  // now mix
  switch (mult) {
    case 1: mix_16h_to_32(buffer, cdda_out_buffer, length*2); break;
    case 2: mix_16h_to_32_s1(buffer, cdda_out_buffer, length*2); break;
    case 4: mix_16h_to_32_s2(buffer, cdda_out_buffer, length*2); break;
  }
}