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
struct TYPE_4__ {int headbit; int headptr; int headend; } ;
typedef  TYPE_1__ oggpack_buffer ;

/* Variables and functions */
 int /*<<< orphan*/  _span (TYPE_1__*) ; 

void oggpack_adv(oggpack_buffer *b,int bits){
  bits+=b->headbit;
  b->headbit=bits&7;
  b->headptr+=bits/8;
  if((b->headend-=bits/8)<1)_span(b);
}