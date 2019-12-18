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
struct TYPE_3__ {char* uus1_data; scalar_t__ remote_operation; scalar_t__ invoke_id; } ;
struct TYPE_4__ {TYPE_1__ dss1; } ;
struct l3_process {TYPE_2__ prot; } ;
struct PStack {int dummy; } ;

/* Variables and functions */
 struct l3_process* new_l3_process (struct PStack*,int) ; 

__attribute__((used)) static struct l3_process
*dss1_new_l3_process(struct PStack *st, int cr)
{  struct l3_process *proc;

   if (!(proc = new_l3_process(st, cr))) 
     return(NULL);

   proc->prot.dss1.invoke_id = 0;
   proc->prot.dss1.remote_operation = 0;
   proc->prot.dss1.uus1_data[0] = '\0';
   
   return(proc);
}