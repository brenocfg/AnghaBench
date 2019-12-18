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

/* Variables and functions */
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  emit_readword_dualindexedx4 (int,int,int) ; 
 int /*<<< orphan*/  emit_readword_indexed (int,int,int) ; 

void emit_readword_indexed_map(int addr, int rs, int map, int rt)
{
  if(map<0) emit_readword_indexed(addr, rs, rt);
  else {
    assert(addr==0);
    emit_readword_dualindexedx4(rs, map, rt);
  }
}