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
struct TYPE_4__ {int endbit; } ;
typedef  TYPE_1__ oggpack_buffer ;

/* Variables and functions */
 int /*<<< orphan*/  oggpack_write (TYPE_1__*,int /*<<< orphan*/ ,int) ; 

void oggpack_writealign(oggpack_buffer *b){
  int bits=8-b->endbit;
  if(bits<8)
    oggpack_write(b,0,bits);
}