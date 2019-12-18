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
typedef  int /*<<< orphan*/  areaseek ;
typedef  int /*<<< orphan*/  arearw ;
typedef  int /*<<< orphan*/  areaeof ;

/* Variables and functions */
 int /*<<< orphan*/ * areaClose ; 
 int /*<<< orphan*/ * areaEof ; 
 int /*<<< orphan*/ * areaRead ; 
 int /*<<< orphan*/ * areaSeek ; 
 int /*<<< orphan*/ * areaWrite ; 
 int pico_state_internal (void*,int) ; 

int PicoStateFP(void *afile, int is_save,
  arearw *read, arearw *write, areaeof *eof, areaseek *seek)
{
  areaRead  = read;
  areaWrite = write;
  areaEof   = eof;
  areaSeek  = seek;
  areaClose = NULL;

  return pico_state_internal(afile, is_save);
}