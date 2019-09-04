#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct tftphdr {int dummy; } ;
struct TYPE_3__ {struct tftphdr hdr; } ;
struct TYPE_4__ {TYPE_1__ buf; int /*<<< orphan*/  counter; } ;

/* Variables and functions */
 int /*<<< orphan*/  BF_ALLOC ; 
 int /*<<< orphan*/  BF_FREE ; 
 TYPE_2__* bfs ; 
 scalar_t__ current ; 
 scalar_t__ newline ; 
 int nextone ; 
 int prevchar ; 

__attribute__((used)) static struct tftphdr *rw_init(int x)
{
  newline = 0;                    /* init crlf flag */
  prevchar = -1;
  bfs[0].counter =  BF_ALLOC;     /* pass out the first buffer */
  current = 0;
  bfs[1].counter = BF_FREE;
  nextone = x;                    /* ahead or behind? */
  return &bfs[0].buf.hdr;
}