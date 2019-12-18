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
struct TYPE_4__ {int /*<<< orphan*/  Seek; int /*<<< orphan*/  Read; int /*<<< orphan*/  Skip; int /*<<< orphan*/  Look; } ;
struct TYPE_5__ {TYPE_1__ s; } ;
typedef  TYPE_2__ CLookToRead ;

/* Variables and functions */
 int /*<<< orphan*/  LookToRead_Look_Exact ; 
 int /*<<< orphan*/  LookToRead_Look_Lookahead ; 
 int /*<<< orphan*/  LookToRead_Read ; 
 int /*<<< orphan*/  LookToRead_Seek ; 
 int /*<<< orphan*/  LookToRead_Skip ; 

void LookToRead_CreateVTable(CLookToRead *p, int lookahead)
{
   p->s.Look = lookahead ?
      LookToRead_Look_Lookahead :
      LookToRead_Look_Exact;
   p->s.Skip = LookToRead_Skip;
   p->s.Read = LookToRead_Read;
   p->s.Seek = LookToRead_Seek;
}