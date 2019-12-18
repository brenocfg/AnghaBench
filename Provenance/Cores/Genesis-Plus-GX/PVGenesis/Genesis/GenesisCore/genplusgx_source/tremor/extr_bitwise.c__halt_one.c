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
struct TYPE_4__ {int headend; } ;
typedef  TYPE_1__ oggpack_buffer ;

/* Variables and functions */
 int /*<<< orphan*/  _adv_halt (TYPE_1__*) ; 

__attribute__((used)) static int _halt_one(oggpack_buffer *b){
  if(b->headend<1){
    _adv_halt(b);
    return -1;
  }
  return 0;
}