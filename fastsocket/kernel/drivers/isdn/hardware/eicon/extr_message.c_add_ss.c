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
typedef  int /*<<< orphan*/  word ;
typedef  size_t byte ;
struct TYPE_3__ {size_t length; size_t* info; } ;
typedef  int /*<<< orphan*/  PLCI ;
typedef  TYPE_1__ API_PARSE ;

/* Variables and functions */
 int /*<<< orphan*/  add_ie (int /*<<< orphan*/ *,size_t,size_t*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dbug (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dprintf (char*,size_t,size_t) ; 

__attribute__((used)) static void add_ss(PLCI   * plci, byte code, API_PARSE * p)
{
  byte i;

  if(p){
    dbug(1,dprintf("add_ss(%x,len=%d)",code,p->length));
    for(i=2;i<(byte)p->length;i+=p->info[i]+2){
      dbug(1,dprintf("add_ss_ie(%x,len=%d)",p->info[i-1],p->info[i]));
      add_ie(plci, p->info[i-1], (byte   *)&(p->info[i]), (word)p->info[i]);
    }
  }
}