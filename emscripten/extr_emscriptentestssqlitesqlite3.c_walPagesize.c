#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int szPage; } ;
struct TYPE_5__ {TYPE_1__ hdr; } ;
typedef  TYPE_2__ Wal ;

/* Variables and functions */

__attribute__((used)) static int walPagesize(Wal *pWal){
  return (pWal->hdr.szPage&0xfe00) + ((pWal->hdr.szPage&0x0001)<<16);
}