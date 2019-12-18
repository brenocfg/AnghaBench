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

/* Variables and functions */
 unsigned int fifo_lastwrite ; 
 unsigned int fifo_latency ; 
 scalar_t__ fifo_write_cnt ; 
 int status ; 

__attribute__((used)) static void vdp_fifo_update(unsigned int cycles)
{
  if (fifo_write_cnt > 0)
  {
    /* Get number of FIFO reads */
    int fifo_read = ((cycles - fifo_lastwrite) / fifo_latency);

    if (fifo_read > 0)
    {
      /* Process FIFO entries */
      fifo_write_cnt -= fifo_read;

      /* Clear FIFO full flag */
      status &= 0xFEFF;

      /* Check remaining FIFO entries */
      if (fifo_write_cnt <= 0)
      {
        /* Set FIFO empty flag */
        status |= 0x200; 
        fifo_write_cnt = 0;
      }

      /* Update FIFO cycle count */
      fifo_lastwrite += (fifo_read * fifo_latency);
    }
  }
}