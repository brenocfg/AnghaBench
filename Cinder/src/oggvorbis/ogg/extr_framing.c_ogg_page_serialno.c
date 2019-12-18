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
struct TYPE_3__ {int* header; } ;
typedef  TYPE_1__ ogg_page ;

/* Variables and functions */

int ogg_page_serialno(const ogg_page *og){
  return(og->header[14] |
         (og->header[15]<<8) |
         (og->header[16]<<16) |
         (og->header[17]<<24));
}