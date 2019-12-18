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

long ogg_page_pageno(const ogg_page *og){
  return(og->header[18] |
         (og->header[19]<<8) |
         (og->header[20]<<16) |
         (og->header[21]<<24));
}