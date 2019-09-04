#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {scalar_t__* pos; scalar_t__ len; } ;
typedef  TYPE_1__ qr_finder_line ;

/* Variables and functions */

__attribute__((used)) static int qr_finder_lines_are_crossing(const qr_finder_line *_hline,
 const qr_finder_line *_vline){
  return
   _hline->pos[0]<=_vline->pos[0]&&_vline->pos[0]<_hline->pos[0]+_hline->len&&
   _vline->pos[1]<=_hline->pos[1]&&_hline->pos[1]<_vline->pos[1]+_vline->len;
}