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
typedef  int /*<<< orphan*/  u32 ;
struct TYPE_2__ {int /*<<< orphan*/ * data32; } ;

/* Variables and functions */
 scalar_t__ calloc (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ *) ; 
 TYPE_1__* scspchannel ; 
 int /*<<< orphan*/  scspsoundbufsize ; 

__attribute__((used)) static int
scsp_alloc_bufs (void)
{
  if (scspchannel[0].data32)
    free(scspchannel[0].data32);
  scspchannel[0].data32 = NULL;
  if (scspchannel[1].data32)
    free(scspchannel[1].data32);
  scspchannel[1].data32 = NULL;

  scspchannel[0].data32 = (u32 *)calloc(scspsoundbufsize, sizeof(u32));
  if (scspchannel[0].data32 == NULL)
    return -1;
  scspchannel[1].data32 = (u32 *)calloc(scspsoundbufsize, sizeof(u32));
  if (scspchannel[1].data32 == NULL)
    return -1;

  return 0;
}